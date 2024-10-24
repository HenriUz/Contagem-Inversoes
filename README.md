# Algoritmo de Inversões entre dois vetores
## Problema
O problema da inversão é interessante, pois ele nos permite, por exemplo, verificar a compatibilidade entre dois usuários de uma plataforma qualque com base em suas listas de preferências.

Esse problema pode descrito como: dado um arranjo `A` contendo `n` inteiros em uma ordem arbitrária, encontrar o número total de inversões, ou seja, o número de pares `(i, j)` de índices `1 < i`, `j < n` tais que `i < j` e `A[i] > A[j]`.

> [!NOTE]
> Perceba que a descrição acima descreve o problema para o número de inversões em um mesmo vetor, e considerando que o vetor normal seria o ordenado.

Sobre a quantidade de inversões, é possível saber a quantidade máxima que um vetor pode ter, com base no seu tamanho. Para isso devemos realizar a combinação da quantidade de elementos a cada 2 `(n 2)` = `n!/(2!(n - 2)!)`.

## Algoritmo Padrão
A primeira coisa a se ter noção, é que força bruta (um `for` dentro do outro) geraria um algoritmo com complexidade `O(n²)`. Com isso, uma solução é buscar fazer um algoritmo de divisão e conquista, em que dividimos o vetor, calculamos a quantidade de inversões em cada uma das partes, e depois calculamos a quantidade de inversões entre as partes.

Porém, é importante notar que a contagem de inversões entre as partes geraria uma complexidade `O(n²)`. Então a solução para fazer em uma complexidade menor é ordenar o vetor, fazendo com que o algoritmo se torne o MergeSort com a adição da contagem de inversões.

## Algoritmo Aplicado 
Neste repositório o algoritmo está um pouco mais complexo, pois o problema descrito acima é aplicado somente para inversões em um vetor e relacionando ele com a sua versão ordenada. Neste caso o problema consiste em calcular o número de inversões entre dois vetores, ou seja, o vetor não pode ser ordenado de acordo com seus números, e sim de acordo a posição dos valores no outro vetor.

Por exemplo os vetores: 
- 1 3 5 2 4 6
- 5 6 1 4 2 3

O número de inversões entre esses dois vetores é 9.

Além disso, também é permitido que os vetores tenham tamanhos diferentes e valores que não sejam correspondentes, por exemplo:
- 1 3 5 2 4
- 5 6 7 1 4 8 9

Felizmente, se o segundo vetor tiver seus elementos mapeados conforme o primeiro, podemos utilizar o algoritmo padrão, pois teremos o mesmo resultado. No caso do exemplo acima, ficaria assim o vetor mapeado: 2 0 4 (se aplicado ao algoritmo padrão, a saída seria 1 inversão).

O problema consiste em como fazer o mapeamento.

Inicialmente pode se pensar em usar um `for` dentro de outro, mas como visto acima isto geraria uma complexidade `O(n²)`, então a solução foi usar alguma estrutura que salve os elementos do primeiro vetor, com o índice, e que permita a busca desses índices em tempo menor do que `n²`. Por isso foi escolhido usar uma Árvore AVL, pois sua inserção e remoção não chegam a ser `n²` e na hora do mapeamento, teremos uma complexidade `O(nlog n)`.