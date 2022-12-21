<?php

// Init
$code = "
  extern int array[];
  extern void update();
";
$ffi = FFI::cdef($code, "./libshared.so");

// Dump
for ($i = 0; $i < 10; $i++) {
  printf("%d, ", $ffi->array[$i]);
}
printf("\n");

// Update
$ffi->update();

// Dump after update
printf("Dump after update:\n");
for ($i = 0; $i < 10; $i++) {
  printf("%d, ", $ffi->array[$i]);
}
printf("\n");

