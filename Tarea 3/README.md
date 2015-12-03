README.md


Vamos a comparar diccionarios implementados con árboles.

> Hipótesis 0: "AVL se comporta mejor que el resto en promedio para búsquedas de strings. La distribución de los string es como una campana de Gauss.(?)"

> Hipótesis 1: "Splay Tree se comporta mejor, su autobalanceo hace que los datos más comunes siempre esten antes."

> Hipótesis 2: "ABB se desempeña mejor que el resto al guardar datos como bits."

> Hipótesis 3: "VEB tiene el mejor ratio noperaciones/tamaño ocupado de los 3 árboles."

Si los datos están bien distribuidos, AVL se comportara mejor que el resto, para la búsqueda. Esto porque elementos que esten más cerca del centro (campana de gauss) serán más comunes y están más arriba del árbol.