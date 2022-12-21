<?php

class Num {
        public int $num = 0;
        public function __construct(int $i)
        {
                $this->num = $i;
        }
}

function &ref(&$array)
{
        $ref = [];
        foreach (array_keys($array) as $key) {
                $ref[] = &$array[$key];
        }
        return $ref;
}

$array = [ new Num(00), new Num(11), new Num(22), 33, 44, 55, 66, 77, 88, 99 ];
$ref = &ref($array);
$ref[0]->num = 345;
var_dump($ref);
var_dump($array);

