# Read ELF #

Many functions in this project come in pairs.
This could be fixed if there was some way to cheese out iheritance or templates.

For now, I'll document the very small differences between these functions.


`flip32_Ehdr` and `flip64_Ehdr`
header type is either `ELf32_Ehdr` or `Elf64_Ehdr`
flipEndian must be called with 32 or 64 for entry
flipEndian must be called with 32 or 64 for phoff
flipEndian must be called with 32 or 64 for shoff


`print32_Ehdr` and `print64_Ehdr`
header type is either `Elf32_Ehdr` or `Elf64_Ehdr`
flip32 or flip64 is used respectively
printf format string for entry must be %x or %lx
printf format string for phoff must be %u or %lu
printf format string for shoff must be %u or %lu
