#!/bin/bash

# Compila o projeto
make clean
make all

# Tamanhos de grid e números de threads a serem testados
grid_sizes=(32 64 128 256 512 1024 2048 4096)
num_threads_omp=(1 2 4 8 16 32)
num_threads_pth=(1 2 4 8 16 32)

# Número de medições para cada experimento
num_measurements=10

# Função para medir o tempo de execução médio e o intervalo de confiança
measure_time() {
    local grid_size=$1
    local impl=$2
    local num_threads=$3

    local total_time=0
    local times=()

    for ((i=0; i<num_measurements; i++)); do
        local output=$(./time_test --grid_size $grid_size --impl $impl --num_threads $num_threads)
        local time=$(echo $output | awk '{print $1}')
        times+=($time)
        total_time=$(echo "$total_time + $time" | bc)
    done

    local avg_time=$(echo "scale=6; $total_time / $num_measurements" | bc)

    # Calcula o desvio padrão
    local sum_sq_diff=0
    for t in "${times[@]}"; do
        local diff=$(echo "scale=6; $t - $avg_time" | bc)
        local sq_diff=$(echo "scale=6; $diff * $diff" | bc)
        sum_sq_diff=$(echo "$sum_sq_diff + $sq_diff" | bc)
    done
    local variance=$(echo "scale=6; $sum_sq_diff / $num_measurements" | bc)
    local stddev=$(echo "scale=6; sqrt($variance)" | bc)

    # Calcula o intervalo de confiança
    local t_value=2.262  # Para um intervalo de confiança de 95% com 9 graus de liberdade
    local confidence_interval=$(echo "scale=6; $t_value * ($stddev / sqrt($num_measurements))" | bc)

    echo "$avg_time $confidence_interval"
}

# Criação do arquivo CSV para armazenar os resultados
echo "grid_size,impl,num_threads,time,confidence_interval" > results.csv

# Executa os experimentos para a versão sequencial
for grid_size in "${grid_sizes[@]}"; do
    time_and_interval=$(measure_time $grid_size "seq" 0)
    avg_time=$(echo "$time_and_interval" | awk '{print $1}')
    confidence_interval=$(echo "$time_and_interval" | awk '{print $2}')
    echo "$grid_size,seq,1,$avg_time,$confidence_interval" >> results.csv
done

# Executa os experimentos para a versão paralelizada com OpenMP
for grid_size in "${grid_sizes[@]}"; do
    for num_threads in "${num_threads_omp[@]}"; do
        time_and_interval=$(measure_time $grid_size "omp" $num_threads)
        avg_time=$(echo "$time_and_interval" | awk '{print $1}')
        confidence_interval=$(echo "$time_and_interval" | awk '{print $2}')
        echo "$grid_size,omp,$num_threads,$avg_time,$confidence_interval" >> results.csv
    done
done

# Executa os experimentos para a versão paralelizada com Pthreads
for grid_size in "${grid_sizes[@]}"; do
    for num_threads in "${num_threads_pth[@]}"; do
        time_and_interval=$(measure_time $grid_size "pth" $num_threads)
        avg_time=$(echo "$time_and_interval" | awk '{print $1}')
        confidence_interval=$(echo "$time_and_interval" | awk '{print $2}')
        echo "$grid_size,pth,$num_threads,$avg_time,$confidence_interval" >> results.csv
    done
done




