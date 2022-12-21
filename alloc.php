<?php

// const NUM_OF_ELEMENTS = 1000 * 1000;
const NUM_OF_ELEMENTS = 1000 * 1000 * 50;

$ar = [
];


$start = microtime(true);
for ($i = 0; $i < NUM_OF_ELEMENTS; $i++) {
  $ar[] = "$i.";
}
echo "\nPush time = " . (microtime(true) - $start) . "\n\n";

// $ar2 = [ ];
// $start = microtime(true);
// for ($i = 0; $i < NUM_OF_ELEMENTS; $i++) {
//   $ar2[$i] = "$i.";
// }
// echo "\nIndex time = " . (microtime(true) - $start) . "\n\n";

