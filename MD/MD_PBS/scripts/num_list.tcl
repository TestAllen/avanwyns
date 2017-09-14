mol load parm7 ../../../data/stripped.prmtop crdbox stripped.mdcrd
set value [lindex $argv 0]
set filename "nums$value.txt"
set fileId [open $filename "a"]
set x 0

while {$x < 1000} {
animate goto $x
display update ui
set sel [atomselect top "(protein and not hydrogen) and within 5 of resid $value"]
set garb [$sel num]
puts $fileId $garb
set x [expr {$x + 1}]
}

quit

