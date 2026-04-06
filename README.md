# Configuração dos Protótipos STEM Criar

Este manual apresenta o passo a passo detalhado para conectar os Protótipos (como o carrinho ou braço robótico) à rede Wi-Fi local e integrá-los ao Servidor STEM Criar.

> **IMPORTANTE:**
>
> 1.  O **Servidor STEM Criar** já deve estar ativado e rodando no seu computador (se necessário, consulte o [Manual de Inicialização do Servidor](https://github.com/stemcriar/servidor-stem-criar?tab=readme-ov-file#servidor-stem-criar))
> 2.  O computador (onde o Servidor está rodando), o seu celular/tablet de controle e o Protótipo **DEVEM estar todos conectados na mesma rede Wi-Fi**.

-----

## Cenário 1. Primeira Conexão (Conectando o Protótipo ao Wi-Fi)

Caso o Protótipo ainda não esteja conectado à rede do laboratório, ou a rede foi trocada, ele criará a sua própria rede para ser configurado.

1.  Ligue o Protótipo (carrinho ou manipulador).
2.  Pegue o seu celular, vá no Wi-Fi e procure por uma rede chamada `Config-ESP-[ID]` (exemplo: `Config-ESP-CAR001`). O `[ID]` único do Protótipo pode ser encontrado colado no adesivo em seu corpo/caixa.
3.  Conecte-se a essa rede. Em poucos segundos, uma tela de configuração abrirá automaticamente no seu aparelho. Caso a tela de configuração não apareça, veja as instruções em [Possíveis Erros¹](#1-a-tela-automática-de-configuração-não-abriu-ao-conectar-na-rede-config-esp).
4.  Na tela que abriu: selecione a primeira opção `Configure WiFi`, procure o nome da rede Wi-Fi do laboratório e digite a senha da rede.
5.  Clique em salvar. O Protótipo irá reiniciar sozinho e se conectar automaticamente ao Wi-Fi se a senha está correta.

> OBS: Caso tenha colocado a senha errada, volte ao Passo 1 do Cenário 1.

<!-- <details>
<summary>Veja mais</summary>
<div align="center">
<img src="img/Passo\_WiFi.gif" alt="Passo a passo da configuração Wi-Fi" width="800">
</div>
</details> -->

-----

## Cenário 2. Apontando o Protótipo para o Servidor

Agora que o Protótipo já está na mesma rede Wi-Fi que você, precisamos informar a ele "onde" o **Servidor STEM Criar** está.

1.  No computador onde o **Servidor STEM Criar** está rodando, observe a barra de endereço do navegador. O número que aparece lá (ex: `192.168.1.15`) é o **IP do Servidor**. Copie esse número.
2.  No seu celular ou computador (que deve estar na mesma rede Wi-Fi do Protótipo e do Servidor), abra o navegador de internet.
3.  Digite o endereço do Protótipo que você quer configurar: `http://[ID].local` (exemplo: `http://CAR001.local`). A página web do Protótipo vai abrir. Caso não abra em alguns segundos, veja [Possíveis Erros²](#2-o-endereço-httpidlocal-não-abre-de-jeito-nenhum)
4.  Nesta página você verá o **IP do Servidor** que o Protótipo está procurando. Se for diferente do número copiado no Passo 1, cole este novo IP na caixa de texto indicada para o Protótipo se conectar ao Servidor.
5.  Clique em **Salvar**. Uma mensagem confirmará que a alteração foi feita.
6.  **Desligue e ligue** o Protótipo no botão para aplicar as mudanças.
7.  Pronto! Verifique a tela principal do seu **Servidor STEM Criar**. O Protótipo deverá aparecer disponível para controle. Caso não apareça, veja [Possíveis Erros³](#3-o-protótipo-não-aparece-no-servidor-mesmo-após-configurar-tudo).

<!-- <details>
<summary>Veja mais</summary>
<div align="center">
<img src="img/Passo\_Servidor.gif" alt="Acessando a página local e salvando IP" width="800">
</div>
</details> -->

-----

## Cenário 3. Alterando a rede Wi-Fi (Mudança de rede enquanto conectado)

Esta alternativa é utilizada para trocar a rede Wi-Fi do Protótipo de forma manual. Ela só faz sentido e só funcionará se o Protótipo **ainda estiver conectado** à rede atual.

> OBS: Se a senha da rede atual foi redefinida, ou se você levou o Protótipo para muito longe do roteador a ponto de perder o sinal, o Protótipo perderá a conexão e entrará automaticamente em modo de configuração. Nesse caso, ignore as etapas abaixo e siga as instruções do [Cenário 1. Primeira Conexão](#cenário-1-primeira-conexão-conectando-o-protótipo-ao-wi-fi).

1.  Acesse a página do Protótipo pelo navegador: `http://[ID].local`.
2.  Role a página até encontrar a seção **Rede Wi-Fi**. Lá, você verá qual é a rede atualmente conectada e uma pergunta logo abaixo: *"Deseja conectar a outra rede?"*
3.  Clique no botão **Esquecer rede atual**.
4.  O Protótipo esquecerá a rede antiga e voltará para o estado inicial (desconectado).
5.  Siga o passo a passo da seção [Cenário 1. Primeira Conexão](#cenário-1-primeira-conexão-conectando-o-protótipo-ao-wi-fi) para encontrar a rede `Config-ESP` e escolher a nova rede Wi-Fi.

<!-- <details>
<summary>Veja mais</summary>
<div align="center">
<img src="img/Passo\_TrocarWiFi.gif" alt="Esquecendo a rede atual" width="800">
</div>
</details> -->

-----

## Possíveis Erros

### 1\. A tela automática de configuração não abriu ao conectar na rede `Config-ESP`.

  * **Causa:** Alguns celulares bloqueiam a abertura automática de portais por segurança.
  * **Solução:** Com o celular ainda conectado à rede `Config-ESP-[ID]`, abra o navegador (Chrome, Safari, etc.) e digite manualmente o endereço `192.168.4.1`. A tela de configuração aparecerá imediatamente.

### 2\. O endereço `http://[ID].local` não abre de jeito nenhum.

  * **Causa:** Alguns aparelhos (especialmente certos modelos de Android) possuem limitações técnicas para ler endereços terminados em `.local`.
  * **Solução:** Tente acessar o endereço utilizando um computador, notebook, iPhone ou iPad conectados na mesma rede Wi-Fi.

### 3\. O Protótipo não aparece no Servidor, mesmo após configurar tudo.

  * **Possibilidade 1:** O Servidor não está ligado. O script `run` precisa ser executado no computador principal antes de tentar controlar o robô.
  * **Possibilidade 2:** Dispositivos em redes diferentes. O computador (Servidor) e o Protótipo **precisam rigorosamente** estar no mesmo Wi-Fi.
  * **Possibilidade 3:** IP do Servidor incorreto. Verifique novamente o endereço IP mostrado no navegador do computador principal e repita os passos do [Cenário 2. Apontando o Protótipo para o Servidor](#cenário-2-apontando-o-protótipo-para-o-servidor).
