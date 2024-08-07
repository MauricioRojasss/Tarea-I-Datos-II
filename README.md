Uso de la aplicación 

Generator
El programa generator es el que utilizo para crear archivos binarios grandes llenos de números enteros aleatorios, para ejecutarlo,  simplemente abro una terminal y escribo el comando ./bin/generator -size <SIZE> 
-output <OUTPUT FILE PATH>, donde <SIZE> puede ser SMALL (512 MB), MEDIUM (1 GB) o LARGE (2 GB). Por ejemplo, si quiero generar un archivo de 512 MB, uso ./bin/generator -size SMALL -output data/input.bin, esto 
creará un archivo binario llamado input.bin en el directorio data/, que contendrá números completamente aleatorios.

Sorter
Para ordenar los números de un archivo binario generado, utilizo el programa sorter, para usarlo, escribo en la terminal ./bin/sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>, aquí,
<INPUT FILE PATH> es la ruta del archivo que quiero ordenar, <OUTPUT FILE PATH> es la ruta donde quiero guardar el archivo ordenado, y <ALGORITMO> es el algoritmo de ordenamiento que quiero usar,como QS para QuickSort.
Por ejemplo, si quiero ordenar el archivo input.bin y guardar el resultado en output.bin utilizando QuickSort, uso ./bin/sorter -input data/input.bin -output data/output.bin -alg QS, al finalizar, el archivo 
output.bin contendrá los números ordenados.

Clase PagedArray
La clase PagedArray es muy importante, ya que gestiona la lógica de paginación. Solo puedo tener cuatro páginas de datos en memoria al mismo tiempo, así que esta clase se encarga de cargar y descargar 
datos desde y hacia el disco, según sea necesario, esto permite que los algoritmos de ordenamiento trabajen como si todos los datos estuvieran en memoria, todo esto se hace de manera transparente, así que no tengo que 
preocuparme por la gestión de la memoria al implementar los algoritmos, al finalizar la ejecución de sorter,se muestra un resumen de las estadísticas, como el número de page faults y page hits, para entender cómo 
funcionó la paginación durante la ejecución.
