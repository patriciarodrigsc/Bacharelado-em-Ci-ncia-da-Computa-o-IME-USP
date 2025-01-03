import matplotlib.pyplot as plt

# Dados da tabela
qntd_threads = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]
tempo_vetor_100 = [0.0004, 0.0006, 0.0007, 0.0010, 0.0018, 0.0041, 0.0061, 0.0096, 0.0152, 0.0304, 0.0592]
tempo_vetor_10000 = [0.0052, 0.0054, 0.0058, 0.0060, 0.0057, 0.0067, 0.0062 , 0.119, 0.0205, 0.0348, 0.0634]
tempo_vetor_1000000 = [0.3388, 0.3000, 0.3016, 0.3008, 0.2989, 0.2995, 0.2996, 0.3022, 3076, 0.3214, 0.3534]

# Configuração da figura
fig, axs = plt.subplots(3, 1, figsize=(8, 10))

# Gráfico 1
axs[0].plot(qntd_threads, tempo_vetor_100, marker='o', label='Tam Vetor = 100')
axs[0].set_xlabel('Qntd Threads')
axs[0].set_ylabel('Tempo Necessário (s)')
axs[0].set_title('Gráfico 1: Tempo Necessário por Qntd Threads (Tam Vetor = 100)')
axs[0].legend()

# Gráfico 2
axs[1].plot(qntd_threads, tempo_vetor_10000, marker='o', label='Tam Vetor = 10000')
axs[1].set_xlabel('Qntd Threads')
axs[1].set_ylabel('Tempo Necessário (s)')
axs[1].set_title('Gráfico 2: Tempo Necessário por Qntd Threads (Tam Vetor = 10000)')
axs[1].legend()

# Gráfico 3
axs[2].plot(qntd_threads, tempo_vetor_1000000, marker='o', label='Tam Vetor = 1000000')
axs[2].set_xlabel('Qntd Threads')
axs[2].set_ylabel('Tempo Necessário (s)')
axs[2].set_title('Gráfico 3: Tempo Necessário por Qntd Threads (Tam Vetor = 1000000)')
axs[2].legend()

# Ajustar espaçamento entre os subplots
plt.tight_layout()

# Exibir os gráficos
plt.show()
