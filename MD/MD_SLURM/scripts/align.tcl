mol new [lindex $argv 3]
mol new [lindex $argv 4]
mol new ../../central.pdb

set first [lindex $argv 0]
set last [lindex $argv 1]
set res [lindex $argv 2]
set sel0 [atomselect 0 all]
set sel1 [atomselect 1 "protein and resid $first to $last"]
set lig [atomselect 2 all]
set M [measure fit $sel0 $sel1]


$lig move $M

set A [atomselect 2 all]

$A writepdb ligand$res.pdb

quit
