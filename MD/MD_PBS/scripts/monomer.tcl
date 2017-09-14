set alignfile [lindex $argv 4]
mol new ../../../data/$alignfile
mol new done.pdb

set res [lindex $argv 0]
set monomer [lindex $argv 1]
set first [lindex $argv 2]
set last [lindex $argv 3]

set sel0 [atomselect 0 all]
set sel1 [atomselect 1 "protein and resid $first to $last"]
set lig [atomselect 1 "resid $res"]
set M [measure fit $sel1 $sel0]

$sel1 move $M
$lig move $M

set A [atomselect 1 "resid $res"]

$A writepdb stuck_$monomer.pdb

quit
