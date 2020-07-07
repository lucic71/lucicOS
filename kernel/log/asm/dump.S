.global reg_dump
.extern printf

.text 

/*
 * reg_dump:
 * -------------
 *
 *  Save the context of caller in prev_* memory locations and print them.
 *
 *  Registers must be saved before calling other routines because they may
 *  change the registers.
 * 
 *  4 is added to prev_esp because current esp has the return address. eip
 *  is fetched by dereferencing esp.
 */


reg_dump:

    mov %esp, prev_esp
    add $0x04, prev_esp

    mov %ebp, prev_ebp

    mov %eax, prev_eax
    mov %ecx, prev_ecx
    mov %edx, prev_edx
    mov %ebx, prev_ebx
    mov %esi, prev_esi
    mov %edi, prev_edi

    mov (%esp), %eax
    mov %eax, prev_eip

    push %ebp
    mov %esp, %ebp

    push $NL_STR
    call printf

    add $0x04, %esp

    push prev_eax
    push $EAX_FMT
    call printf

    add $0x08, %esp

    push prev_ecx
    push $ECX_FMT
    call printf

    add $0x08, %esp

    push prev_edx
    push $EDX_FMT
    call printf

    add $0x08, %esp

    push prev_ebx
    push $EBX_FMT
    call printf

    add $0x08, %esp

    push prev_esp
    push $ESP_FMT
    call printf

    add $0x08, %esp

    push prev_ebp
    push $EBP_FMT
    call printf

    add $0x08, %esp

    push prev_esi
    push $ESI_FMT
    call printf

    add $0x08, %esp

    push prev_edi
    push $EDI_FMT
    call printf

    add $0x08, %esp

    push prev_eip
    push $EIP_FMT
    call printf

    add $0x08, %esp

    mov %ebp, %esp
    pop %ebp

    ret

.data

    NL_STR: .string "\n"
    EAX_FMT: .string "eax: 0x%x\n"
    ECX_FMT: .string "ecx: 0x%x\n"
    EDX_FMT: .string "edx: 0x%x\n"
    EBX_FMT: .string "ebx: 0x%x\n"
    ESP_FMT: .string "esp: 0x%x\n"
    EBP_FMT: .string "ebp: 0x%x\n"
    ESI_FMT: .string "esi: 0x%x\n"
    EDI_FMT: .string "edi: 0x%x\n"
    EIP_FMT: .string "eip: 0x%x\n"

.bss

    prev_eax: .skip 4
    prev_ecx: .skip 4
    prev_edx: .skip 4
    prev_ebx: .skip 4
    prev_esp: .skip 4
    prev_ebp: .skip 4
    prev_esi: .skip 4
    prev_edi: .skip 4
    prev_eip: .skip 4
