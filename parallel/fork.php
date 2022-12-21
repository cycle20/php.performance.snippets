<?php

require __DIR__ . "/vendor/autoload.php";

use Spatie\Fork\Fork;


$x = function ($i, $signal) {
    for ($index = 0; $index < 10; $index++) {
        printf("$signal");
        //sleep(random_int(3, 10));
        //sleep(1);
    }
    return printf("\n$i done.\n");
};

$fork = Fork::new();
$batch = [];
$i = 1;
$batch[] = fn () => $x($i++, "A");
$batch[] = fn () => $x($i++, "B");
$batch[] = fn () => $x($i++, "C");

print_r($batch);

$fork->run(...$batch);

$x($i++, "D");
