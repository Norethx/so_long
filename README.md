# 🎮 so_long

Esse foi o meu primeiro programa desenvolvido na 42.  
O projeto faz parte do **ML 2**, sendo um dos três projetos gráficos que podemos escolher nesse módulo.

---

## ❓ Por que escolhi o *so_long*?

De forma resumida: eu cresci e respirei jogos grande parte da minha vida.  
Fazer o *so_long* foi uma oportunidade de entender práticas de criação de jogos sem necessariamente usar *game maker* ou *Godot*.  

Além disso, sem dúvidas é um **pontapé inicial 🚀** para um mercado no qual pretendo seguir.

---

## 🧩 O que é *so_long*?

Basicamente é um programa que:

1. 📂 Lê um arquivo `.ber`.  
2. ✅ Passa por uma tratativa de erros.  
3. 🖼️ Caso o arquivo seja válido, desenha na tela um jogo.  

### ⚔️ Regras principais

- O objetivo do player é pegar todos os coletáveis.  
- Para ganhar, deve chegar até a saída.  

### ⭐ Funcionalidades bônus

- 👾 Adição de patrulhas.  
- 🌀 Sprites animados.  

🎯 O objetivo maior é **aprender a carregar/manipular imagens** e **tratar erros ao parsear arquivos**.

---

## 🛠️ Desenvolvimento do projeto

### 📚 Escolha da biblioteca gráfica

O primeiro passo foi analisar as opções:  

- **Minilibx** → mais antiga, compatibilidade menor em alguns sistemas.  
- **MLX42** → projeto *open source* criado por cadetes do campus de Amsterdã.  
  - Usa **OpenGL**.  
  - Melhor desempenho.  
  - Permite subir `.png` direto como textura.  

👉 Eu escolhi a **MLX42**.

---

### 📝 Parsing e validação do mapa

Após definir a biblioteca, comecei pela validação do arquivo `.ber`.  
Critérios implementados:

- 📌 Extensão obrigatória `.ber`.  
- 📏 Todas as linhas precisam ter o mesmo tamanho.  
- 🧱 O mapa deve estar rodeado por paredes.  
- 🕹️ Deve ter tamanho mínimo jogável.  
- ✔️ Validações específicas:  
  - Quantidade de coletáveis.  
  - Quantidade de saídas.  
  - Quantidade de posições iniciais do player.  
- 🔗 Deve ser possível coletar todos os itens e alcançar a saída.

---

### 🖼️ Primeiros testes na MLX

Antes de aplicar no projeto, criei um arquivo separado só para testes:  

- Abrir a tela.  
- Carregar um `.png`.  
- Implementar *hooks* de teclas.  
- Testar bloqueio de movimento usando um *array* guia (paredes invisíveis).  

⚡ Depois de alguns dias de testes, me senti pronto para aplicar no projeto oficial.

---

## ⚡ Problemas enfrentados

### 🎨 Escolha de sprites

A parte mais complicada foi a **criativa**.  
Depois de algumas horas garimpando no [Itch.io](https://itch.io), encontrei sprites com perspectiva *top-down* que gostei:  

👉 [Dungeon Tileset II](https://0x72.itch.io/dungeontileset-ii)

---

### 🌀 Questão da profundidade

No início, eu renderizava categoria por categoria, nessa ordem:  

1. Floors  
2. Walls  
3. Collectables  
4. Player  

🚨 O problema: os sprites tinham tamanhos diferentes e perspectiva, fazendo o player se sobrepor a alguns itens, quebrando a noção de profundidade.

#### ✅ Solução adotada

- Renderizar linha a linha (de cima para baixo).  
- Cada linha assume profundidade menor que a seguinte.  
- A cada movimento, o player atualiza sua profundidade com base na linha em que está.  

💡 Isso resolveu o problema!

---

### 👥 Estrutura para *childs*

Criei uma estrutura para *childs* (player e patrulhas):  

- Continha todas as imagens necessárias para as animações.  
- A cada movimento, todas as imagens se movem juntas.  
- Apenas o sprite correto da animação fica ativo.  
- O mesmo vale para o estado *idle*.  

---

## 💻 Como compilar o projeto?

1. 🐧 Recomendo usar **Linux**.  
   - Caso esteja no **Windows**, use **WSL 2**.  
   - Atenção: será necessário configurar o display do Windows para rodar a MLX42.  

2. Clone este repositório:  
   ```bash
   git@github.com:Norethx/so_long.git
   ```

3. Clone também a MLX42 dentro da pasta do projeto:  
  ```bash
  git clone https://github.com/codam-coding-college/MLX42
  ```

4. Compile:
# Projeto obrigatório
  ```bash
  make
  ```
# Projeto com bônus
```bash
make bonus
```

5. Execute:
```bash
./so_long caminho/para/mapa.ber
```

👉 Já existem mapas de exemplo no repositório:
- maps/ → mapas simples.
- maps/bonus/ → mapas com patrulhas.

---

## ⚠️ Observações

- Nos computadores da 42, cc é mapeado para gcc.
- Caso tenha erro de compilação, altere a variável CC no Makefile para gcc.

---

✍️ Esse foi um dos projetos mais divertidos de implementar até agora. Espero que gostem do resultado tanto quanto eu gostei de desenvolvê-lo!
