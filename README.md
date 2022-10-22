# Proyecto 1 : Aplicación _Chat_

## Creación de apliación
 En el directorio raíz:

```
meson target
```

## Compilación

Dentro del directorio `target`:

```
meson compile
```

## Ejecución

Ejecutable localizado dentro de la capreta `proyecto1/target/`.



En directorio `target`:

```
./proyecto1
```


La elección del lenguaje de programación se ha visto grandemente influenciada
por la preferencia a la orientación a objetos que los proyectos de este curso
poseen. Además, consideré que, de entre este tipo de lenguajes, C++ destaca como
uno de los más rápidos y eficientes (debido a su bajo nivel). Por estas razones,
esta ha sido una herramienta clara para el desarrollo de estos problemas.

## Uso

El chat comenzará pidiendo que el usuario elija si desea iniciar el cliente o el
servidor.

### Servidor

Se pedirá la introducción de un puerto en el cual enlazar el socket.

Después de ello, se mostrará una interfaaz simplificada que mostrará conexiones
y desconexiones de los usuarios.

### Cliente

En este caso, se pedirá la introducción de un puerto e ip (de un servidor que implemente
el protocolo convenido).

Una vez establecida la conexión se presentará una interfaz en la que es posible
consultar la lista de usuarios (esquina superior derecha), crear salas (símbolo +),
cambiar su estado (esquina superior izquierda), mandar mensajes privados (doble click sobre
alguno de los usuarios de la lista presentada) e invitar usuarios a un grupo (seleccionándolos
con click izquierdo; aparecerá un botón en la parte superior de la interfaz para confirmar
la elección; se tiene que elegir persona por persona).

## Diseño

El diseño gira alrededor del modelo vista controlador, donde la clase _Chat_ funge como el
controlador; el servidor y el cliente, como el modelo; y las vistas de tanto el servidor
como el cliente, como la vista.

Decidí usar el patrón singleton para la clase Chat, esto derivado del papel como controlador
de la aplicación, funge como la sesión de la aplicación.

Otro par de clases que también cuentan con este diseño, son Vista_Cliente y Vista_Servidor;
las razones son similares con la clase Chat; de cierta manera, representan la sesión de la
aplicación y, por lo tanto, no deseamos que haya más de una instancia de las mismas.

Otro patrónde diseño a destacar es el método fábrica, incluido para crear los procesadores
tanto del servidor como del cliente; esto con el motivo de reducir el código escrito
(creando instancias de procesadores a partir del protocolo recibido) así como en favor
de una mejor claridad (en la mayoría de los casos).


       
