#!/usr/bin/perl -wl

$number = 5;
$string = "String";
$multilined_string = <<EOF;
Multilined string,
terminating with the word "EOF".
EOF

@array = (1, 2, "three");
print $array[1]; # "2"

%hash = ('one' => 1, 'two' => 2);
print $hash{'one'}; # "1"

$ref = \$number;
print $ref; # SCALAR(0x14ef640)
print $$ref; # 5

$circle={
  center=>{x=>210, y=>297},
  radius=>53,
};
