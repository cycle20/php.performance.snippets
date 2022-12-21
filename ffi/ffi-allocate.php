<?php

// Init
$code = "
  extern void allocate(unsigned int);
  extern void dispose();
";
$ffi = FFI::cdef($code, "./libshared.so");

// Allocate
$sleep = 10;
printf("Sleep before allocating\n");
sleep($sleep);
// let's try to allocate for 1million atoms
$ffi->allocate(1000 * 1000);

// Clean up stuff
printf("Sleep before dispose\n");
sleep($sleep);
$ffi->dispose();

printf("Sleep after dispose\n");
sleep($sleep);

