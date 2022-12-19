<?php

# From https://forum.yiiframework.com/t/php-objects-vs-arrays-performance-myth/28271

define('NUM_INSTANCES', 10);
define('NUM_TESTS', 10000);

class TestObject
{
  public $a;
  public $b;
  public $c;

  public function __construct($a,$b,$c)
  {
    $this->a = $a;
    $this->b = $b;
    $this->c = $c;
  }
}


class Test
{
  public function getObjects()
  {
    $a = array();
    for ($i=0; $i<NUM_INSTANCES; $i++)
      $a[] = new TestObject('a','b','c');
    return $a;
  }

  public function getArrays()
  {
    $a = array();
    for ($i=0; $i<NUM_INSTANCES; $i++)
      $a[] = $this->buildArray('a', 'b', 'c');
    return $a;
  }

  public function buildArray($a, $b, $c)
  {
    $array = array();
    $array['a'] = $a;
    $array['b'] = $b;
    $array['c'] = $c;
    return $array;
  }

  public function useObject($o)
  {
    $a = $o->a;
    $b = $o->b;
    $o->c = 'xxx';
  }

  public function useArray($o)
  {
    $a = $o['a'];
    $b = $o['b'];
    $o['c'] = 'xxx';
  }
}


$test = new Test;

//
///////////////////////////// Benchmark with objects:
//
$start = microtime(true);
for ($i=0; $i<NUM_TESTS; $i++)
{
  $x = $test->getObjects();
  foreach ($x as $y)
    $test->useObject($y);
}

echo "\nObject time = " . (microtime(true)-$start) . "\n\n";


//
///////////////////////////// Benchmark with arrays:
//
$start = microtime(true);
for ($i=0; $i<NUM_TESTS; $i++)
{
  $x = $test->getArrays();
  foreach ($x as $y)
    $test->useArray($y);
}

echo "\nArray time = " . (microtime(true)-$start) . "\n\n";

