braco-mecanico
==============

Estudo sobre estrutura de dados em C
Mundo dos Blocos
----------------

Disponível em https://github.com/paidico/braco-mecanico.git

* Setup
  * Linux
    * RPM-based ([Fedora](https://fedoraproject.org/en/get-fedora))
    ```SH
    $ su -c "yum groupinstall development-tools"
    ```
    * Debian-based ([Ubuntu](http://www.ubuntu.com/download))
    ```SH
    $ sudo apt-get install build-essential
    ```
  * Mac OSX
    * Basta instalar o `XCode`
    ```
    ```
  * Windows
    * Virtualize um SO Linux (sugiro usar o [Oracle VM VirtualBox](https://www.virtualbox.org/) para isso)
    * Ou use um sistema Linux [`live bootable`](https://fedoraproject.org/en/get-fedora)
    * Ou desista da Microsoft
    * Ou compile diretamente os arquivos um a um ou com alguma ferramenta que eu desconheço
    ```
    ```
* Compilação
```SH
$ cd caminho/ate/braco-mecanico
$ make
```
* Execução
```SH
$ ./bin/bracomec arquivo_com_instrucoes
$ cat out.txt
```
