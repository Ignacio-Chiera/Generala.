	.data
slist:  .word 0
cclist:	.word 0
wclist:	.word 0
schedv: .space 32
menu:	.ascii "Colecciones de objetos categorizados\n"
	.ascii "====================================\n"
	.ascii "1-Nueva categoria\n"
	.ascii "2-Siguiente categoria\n"
	.ascii "3-Categoria anterior\n"
	.ascii "4-Listar categorias\n"
	.ascii "5-Borrar categoria actual\n"
	.ascii "6-Anexar objeto a la categoria actual\n"
	.ascii "7-Listar objetos de la categoria\n"
	.ascii "8-Borrar objeto de la categoria\n"
	.ascii "0-Salir\n"
	.asciiz "Ingrese la opcion deseada: "
error:	.asciiz "Error: "
return:	.asciiz "\n"
catName:.asciiz "\nIngrese el nombre de una categoria: "
selCat:	.asciiz "\nSe ha seleccionado la categoria:"
idObj:	.asciiz "\nIngrese el ID del objeto a eliminar: "
objName:.asciiz "\nIngrese el nombre de un objeto: "
success:.asciiz "La operación se realizo con exito\n\n"

error2: .asciiz "Error: Opcion invalida\n"

	.text 0x00400000   # Dirección inicial para código
main:
    jal print_menu         # Imprimir el menú
    j loop

    #jal get_option         # Leer la opción ingresada por el usuario
    #jal validate_option
    
    li $v0, 10             # Exit syscall
    syscall

print_menu:
    la $a0, menu           # Cargar la dirección del menú
    li $v0, 4              # Syscall para imprimir string
    syscall
    
loop:
    jal get_option         # Leer la opción ingresada por el usuario (una sola vez por iteración)
    bltz $t0, invalid      # Si el valor es menor que 0, salta a "invalid"
    li $t1, 8
    bgt $t0, $t1, invalid  # Si el valor es mayor que 8, salta a "invalid"
     # Si el input es válido, simplemente salimos del bucle y continuamos con el resto del programa
    j continue_execution   # Saltamos a la siguiente parte del programa

get_option:
    li $v0, 5             # Syscall para leer un entero
    syscall
    move $t0, $v0         # Guardar el valor leído en $t0
    #jr $ra                # Retornar a main

    
validate_option:
    bltz $t0, invalid     # Si el valor es menor que 0, es inválido
    li $t1, 8
    bgt $t0, $t1, invalid # Si el valor es mayor que 8, es inválido
    jr $ra                # Si es válido, retorna a main

invalid:
    la $a0, error2         # Cargar el mensaje de error
    li $v0, 4             # Syscall para imprimir string
    syscall
    jal print_menu        # Volver a imprimir el menú
    jr $ra                # Retornar a main
    
continue_execution:
    # Aquí va el código que deseas ejecutar después de recibir un input válido
    # Por ejemplo, puedes procesar la opción y luego salir del programa si es 0
    beqz $t0, exit         # Si el input es 0, salir del programa
    # Opciones adicionales se implementan aquí...
   #hola

exit:
    li $v0, 10             # Exit syscall
    syscall