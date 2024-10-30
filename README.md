# Algoritmo de Inversões entre dois vetores
## Problema
O problema da inversão é interessante, pois ele nos permite, por exemplo, verificar a compatibilidade entre dois usuários de uma plataforma qualquer com base em suas listas de preferências.

Esse problema pode descrito como: dado um arranjo `A` contendo `n` inteiros em uma ordem arbitrária, encontrar o número total de inversões, ou seja, o número de pares `(i, j)` de índices `1 < i`, `j < n` tais que `i < j` e `A[i] > A[j]`.

> [!NOTE]
> Perceba que a descrição acima descreve o problema para o número de inversões em um mesmo vetor, e considerando que o vetor normal seria o ordenado.

Sobre a quantidade de inversões, é possível saber a quantidade máxima que um vetor pode ter, com base no seu tamanho. Para isso devemos realizar a combinação da quantidade de elementos a cada 2 `(n 2)` = `n!/(2!(n - 2)!)`.

## Algoritmo Padrão
Uma abordagem inicial, e até ingênua, seria usar a força bruta, ou seja, percorrer o vetor comparando elemento por elemento. Em código, isso seria um `for` dentro de outro, resultando em um algoritmo `O(n²)`.

Então, outra ideia seria usar divisão e conquista para resolver o problema. Dessa forma, a ideia seria dividir o vetor em duas partes, e com isso seria contado o número de inversões em cada uma delas. No final, faltaria contar as inversões entre as partes.

Infelizmente, contar as inversões entre as partes também resultaria em um algoritmo `O(n²)`. Mas esse não é o fim do mundo, pois uma solução encontrada seria contar as inversões enquanto ordena o vetor, fazendo com que o algoritmo se torne algo parecido com o MergeSort, de complexidade `O(nlog(n))`, em que as inversões seriam incrementadas, na função Merge, toda vez que um elemento do vetor da direita entrar no vetor auxiliar na frente de um da esquerda.

## Sobre o Projeto
O algoritmo deste projeto foi desenvolvido para resolver o problema da inversão, mas com o diferencial das inversões serem entre dois vetores, e não 1 como visto acima, além disso, neste novo problema a ordem correta não é a ordenada, e sim a de algum vetor, e os vetores não precisam ser do mesmo tamanho e podem ter elementos diferentes entre si.

A estratégia implementada foi mapear o segundo vetor conforme as posições do primeiro, e dessa forma podemos utilizar o algoritmo padrão nesse vetor mapeado que a quantidade de inversões será a mesma, segue o exemplo.

Vetores originais (9 inversões):

- 1 3 5 2 4 6
- 5 6 1 4 2 3

Após o mapeamento o segundo ficará:

- 2 5 0 4 3 1

Para garantir que o algoritmo tenha uma complexidade `O(nlog(n))`, foi usado uma Árvore AVL para armazenar os elementos do primeiro vetor, com os índices. Isso garante a complexidade `O(nlog(n))` porque a busca na árvore é `O(log(n))` e o percorrimento do segundo vetor é `O(n)`.

> [!note]
> Perceba que a parte da inversão também é `O(nlog(n))`, então a complexidade do algoritmo também será `O(nlog(n))`.

## Organização
/Casos-De-Teste: contém os arquivos de entrada (`.in`), e o valor esperado para eles (`.out`). Os arquivos `.in` seguem a seguinte estrutura: tamanho-vetor-1 → vetor-1 → tamanho-vetor-2 → vetor-2.

main.c: algoritmo implementado.