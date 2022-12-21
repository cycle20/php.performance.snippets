<?php

$x = function ($i, $signal) {
    for ($index = 0; $index < 10; $index++) {
        printf("$signal");
        //sleep(random_int(3, 10));
        //sleep(1);
    }
    return printf("\n$i done.\n");
};

$batch = [];
$i = 1;
$batch[] = new Fiber(fn () => $x($i++, "C"));
$batch[] = new Fiber(function () use (&$i, $x) { $x($i++, "A"); });
$batch[] = new Fiber(function () use (&$i, $x) { $x($i++, "B"); });

print_r($batch);
foreach ($batch as $job) {
    $job->start();
}
$x($i++, "D");
