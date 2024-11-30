@echo off
gcc main.c abr.c Btree.c listbd.c Max-heap.c Min_heap.c ../TriParTas/Merge_Sort.c ../TriParTas/Sort_Heap.c ../TriParTas/TriRapide.c ../TriParTas/gnomeSort.c -o main
if %errorlevel% equ 0 (
    .\main
) else (
    echo Compilation failed.
)
pause