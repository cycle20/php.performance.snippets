<?php

class C {
  public array $ar = [ ];

  public function __construct() {}
}

function update(array &$ar, $i) {
  $ar[$i] = "UPDATED";
}

$c = new C();
$c->ar[0] = "Zero";
$c->ar[1] = "One";
$c->ar[2] = "Two";
$c->ar[3] = "Three";

print_r($c->ar);

$ref = &$c->ar;

update($ref, 1);


print_r($ref);

