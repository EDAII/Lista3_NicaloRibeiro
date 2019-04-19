# Lista 3 -- Algorítmos de Ordenação

| Aluno          | Matrícula  |
|----------------|------------|
| Nícalo Ribeiro | 16/0016169 |
---
## Funcionamento básico do programa
* É necessário a instalação do GNUPLOT
~~~
sudo apt-get install gnuplot
~~~
* O programa realizará a leitura de um arquivo com dados públicos relacionados ao cadastro das casas legislativas do Brasil;
* Esses dados podem ser encontrados neste [site](http://dados.gov.br/dataset/censo-do-legislativo/resource/b758a7e0-069c-493e-8d56-836610eb565c "Dados casas legislativas");
* Outros dados públicos podem ser acessados no site [Dados](http://dados.gov.br/ "Dados Gov");
* O aquivo foi tratado, com a exclusão de categorias de dados incompletos ou incoerentes, sobrando as seguintes categorias :  
       - Cod_TSE,Cod_IBGE,UF,localidade,Regiao,Microregiao,População;
* Será possível realizar ordenaçoes por Cod_TSE,Cod_UBGE e População;

  