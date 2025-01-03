import pandas as pd
import matplotlib.pyplot as plt

# Carrega os dados do arquivo CSV em um DataFrame
df = pd.read_csv('results.csv')

# Filtra os dados para cada implementação (seq, omp e pth)
df_seq = df[df['impl'] == 'seq']
df_omp = df[df['impl'] == 'omp']
df_pth = df[df['impl'] == 'pth']

# Plota gráficos para cada implementação (seq, omp e pth)
fig, axes = plt.subplots(nrows=3, ncols=1, figsize=(10, 10))

# Função para plotar gráficos com múltiplas linhas e barras de erro
def plot_lines_with_errorbars(ax, df, label_prefix):
    num_threads = sorted(df['num_threads'].unique())
    for threads in num_threads:
        data = df[df['num_threads'] == threads]
        ax.errorbar(data['grid_size'], data['time'], yerr=data['confidence_interval'], label=f"{label_prefix} {threads} threads", capsize=4)
    ax.set_xlabel('Tamanho da grid')
    ax.set_ylabel('Tempo de execução (s)')
    ax.legend()

# Plot para a implementação sequencial
plot_lines_with_errorbars(axes[0], df_seq, 'Sequencial')
axes[0].set_title('Implementação Sequencial')

# Plot para a implementação omp
plot_lines_with_errorbars(axes[1], df_omp, 'OMP')
axes[1].set_title('Implementação OMP')

# Plot para a implementação pth
plot_lines_with_errorbars(axes[2], df_pth, 'PTH')
axes[2].set_title('Implementação PTH')

plt.tight_layout()
plt.show()
