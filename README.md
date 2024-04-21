# SSL_deane_sofia
Repo para los TPs de Sintaxis y Semantica de los Lenguajes
UTN - FRBA
Sintaxis y Semántica de los Lenguajes
Trabajo Práctico n° 0 - Primeros pasos en Git, GitHub, Compilador, IDE

Para trabajar durante la cursada, es necesario que conozcas la herramienta Git, la plataforma GitHub y que instales tu entorno de desarrollo para poder llevar adelante los trabajos prácticos grupales. Los pasos a seguir para el trabajo práctico n° 0 (individual) son los siguientes:


Si aún no posees una cuenta en GitHub, regístrate utilizando tu correo institucional provisto por la facultad (@frba.utn.edu.ar). En caso de ya tener una cuenta creada, te solicitamos vincularla con tu mail institucional. Este punto es indispensable para que luego podamos enviarte una invitación para que obtengas acceso al repositorio designado para tu equipo. Por lo tanto, es obligatorio que sea con el mail institucional.


Nota: actualmente, con tu cuenta institucional de la facultad puedes acceder a un beneficio con tu cuenta de GitHub. Instructivo para obtenerlo.


Para continuar, te pedimos que veas los videotutoriales, guías y/o apuntes en la sección de Git y GitHub del aula virtual para entender en qué consisten ambas y su uso.
Allí encontrarás más información sobre cómo realizar los pasos que siguen.


Descargar e instalar Git, si aún no lo tienes.


Crear un repositorio público con la siguiente nomenclatura: SSL_apellido_nombre
Puedes hacerlo desde el navegador web directamente en GitHub.


Clonar el repositorio remoto de GitHub a tu computadora, si lo has creado desde el navegador web. Es mediante el comando git clone pasándole como argumento una dirección que podrás encontrar en tu repositorio en GitHub. No lo descargues como un archivo ZIP desde GitHub o no vas a poder trabajarlo como un repositorio local.


Nota: en Windows, asegúrate de ejecutar los comandos de Git (como el anterior) en la consola de Git que te pedimos que instales en el paso 3). Para la materia, en general evitaremos PowerShell o el Command-Prompt (cmd) para evitar confusiones; únicamente utilizaremos la consola de Git. Tenlo en cuenta de ahora en más.


Aclaración: nos referimos con repositorio remoto a aquel que está almacenado en un servidor de alojamiento de proyectos que usen Git, como lo es GitHub. Son usados para compartir nuestro código fuente con otras personas vía Internet.
Por otro lado, denominamos como repositorio local a cada uno de los “clones” que tengamos del remoto en nuestras computadoras. Éstos permiten que los desarrolladores puedan trabajar en ese mismo código descargado, realizar cambios y luego sincronizarlos con el resto por medio del remoto cuando estén listos.
Por regla general, no le aplicamos cambios directos a los archivos fuente del repositorio remoto desde GitHub, sino que debemos traerlo a nuestra computadora, hacer los cambios necesarios en nuestro repositorio local, y recién luego llevarlos hacia el remoto.


Abrir el directorio del repositorio local en tu computadora (recién “clonado” del remoto). El mismo debería tener el mismo nombre que el que le pusiste a tu repositorio, entonces el formato tendría que ser SSL_apellido_nombre. A dicho directorio lo podemos denominar como la raíz del repositorio (porque contiene todos los archivos y subdirectorios que haya dentro de éste).


Nota: directorio es el término formal para carpeta (ambos hacen referencia al mismo concepto).


Crear un archivo README.md en la raíz de tu repositorio local (si aún no lo tienes creado). En dicho archivo escribe algún mensaje describiendo tu repositorio, por ejemplo, puedes poner “Este es mi repositorio para la cursada de Sintaxis y Semántica de Lenguajes”. Este texto es tan solo un ejemplo, pero puedes incluir otro que creas conveniente.


Nota: Los archivos con extensión .md (markdown) son archivos de texto plano que puedes crear, abrir, editar y guardar con cualquier editor de texto; tan solo tienes que cambiar el nombre del archivo de texto para que tenga dicha extensión.
Markdown es un lenguaje de marcado ligero: tiene una notación especial para especificar el formato del texto de manera sencilla (ej. colocar encabezados, poner en negrita, insertar tablas, imágenes, etc.).
La sintaxis de los archivos markdown puede ser interpretada de distintas formas dependiendo de la herramienta que las procese (el lenguaje no está muy estandarizado). Es decir que un archivo .md que se visualice correctamente en una plataforma no necesariamente se verá bien en otra, y viceversa.
En GitHub, cada archivo README.md actúa como portada del directorio que lo contiene en el repositorio remoto. Sintaxis de escritura y formatos básicos en GitHub.


Dentro de tu mismo repositorio local, crear también un subdirectorio con el nombre 00-PrimerProgramaC.


Dentro de dicho subdirectorio, crear y escribir otro archivo README.md que actúe como portada de la resolución del TP0 con una breve explicación de lo que van a desarrollar en lenguaje C.


Instalar un compilador del lenguaje C. Para la materia, pedimos que utilicen gcc (GNU C Compiler) (que a su vez forma parte de GCC (GNU Compiler Collection)). En Windows, puedes hacerlo a través del proyecto MinGW. En el aula virtual hay instructivos que pueden guiarte.


Instalar un editor de código fuente (no necesariamente un IDE). Aunque no es obligatorio, les recomendamos utilizar Visual Studio Code para la materia, ya que posee extensiones de resaltado no sólo para código en C sino también para los demás archivos de especificación que veremos durante la cursada; así como otras extensiones para facilitar la depuración de código en C, etc.
También hay material en el aula virtual al respecto que puede serte de utilidad.


Crear y escribir un programa en lenguaje C muy simple, por ejemplo, uno que solamente imprime “Hola mundo”. Al archivo puedes nombrarlo, por ejemplo, simplemente: archivo.c


Compilar dicho programa y ejecutarlo para comprobar su correcto funcionamiento.


Publicar dicho programa así como los demás cambios en tu repositorio remoto de GitHub creado. Para el programa solamente es necesario el archivo .c. Puedes hacerlo utilizando la sucesión de comandos git add . , git commit -m 'Mensaje' y git push para llevar modificaciones en tu repositorio local al remoto.


Nota: ten en cuenta que Git ignora los directorios que estén vacíos, así como aquellos archivos que estén indicados en un archivo .gitignore.


En la planilla de grupos (la cual estará disponible en el aula virtual), cargar junto al resto de los datos solicitados el link a su repositorio individual de GitHub, a modo de confirmar la entrega de tu TP0.

Este trabajo no tiene una entrega con nota, pero sí es necesario que lo realices y que dejes un enlace a tu repositorio remoto creado en la planilla de formación de equipos. Su fecha límite para consultas y realización es el día domingo 21 de abril.

Las consultas podrán ser realizadas a través de Discord.
