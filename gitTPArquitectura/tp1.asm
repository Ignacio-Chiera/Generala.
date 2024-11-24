.data 0x10010000   # Dirección inicial para datos
slist:  .word 0    # Lista de Bloques liberados
cclist: .word 0    # Lista de categorias
wclist: .word 0    # Categoria seleccionada
schedv: .space 32  # Vector de direcciones del menu, toma 32 espacios de memoria en el "data segment"

menu:   .ascii  "Menu de categorias y objetos:\n"
        .ascii  "=================================\n"
        .ascii  "1- Nueva categoria\n"
        .ascii  "2- Seleccionar siguiente categoria\n"
        .ascii  "3- Seleccionar categoria anterior\n"
        .ascii  "4- Listar categorias\n"
        .ascii  "5- Borrar categoria seleccionada\n"
        .ascii  "6- Anexar objeto a la categoria actual\n"
        .ascii  "7- Listar objetos de la categoria actual\n"
        .ascii  "8- Borrar objeto por ID\n"
        .ascii  "0- Salir\n"
        .asciiz "Ingrese una opcion: "
        
error: .asciiz "Error: Opcion invalida\n"

        
.text 0x00400000   # Dirección inicial para código
main:
    jal print_menu         # Imprimir el menú
    jal get_option         # Leer la opción ingresada por el usuario
    jal validate_option
    
    li $v0, 10             # Exit syscall
    syscall

print_menu:
    la $a0, menu           # Cargar la dirección del menú
    li $v0, 4              # Syscall para imprimir string
    syscall

get_option:
    li $v0, 5             # Syscall para leer un entero
    syscall
    move $t0, $v0         # Guardar el valor leído en $t0
    jr $ra                # Retornar a main
    
validate_option:
    bltz $t0, invalid     # Si el valor es menor que 0, es inválido
    li $t1, 8
    bgt $t0, $t1, invalid # Si el valor es mayor que 8, es inválido
    jr $ra                # Si es válido, retorna a main

invalid:
    la $a0, error         # Cargar el mensaje de error
    li $v0, 4             # Syscall para imprimir string
    syscall
    jal print_menu        # Volver a imprimir el menú
    jr $ra                # Retornar a main