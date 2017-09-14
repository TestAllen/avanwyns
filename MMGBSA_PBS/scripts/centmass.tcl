mol load parm7 XXX/data/complex_GB.prmtop
set x 0
while {$x < YYY} {
	set first [expr {$x * 25000}]
	set prolast [expr {$x * 25000}]
	set eulast [expr {$prolast + 24999}]
	animate read crd XXX/master.mdcrd beg $first end $eulast waitfor all top
	set sel0 [atomselect top "resname MOL"]
	set filename XXX/../mapping/centmass_temps/centmass_$x
	set fileId [open $filename "w"]
	set n [molinfo top get numframes]
	puts $n
	set y 0
	while {$y < $n} {
		animate goto $y
		display update ui
		set com1 [measure center $sel0 weight mass]
		puts $fileId "$com1"
		set y [expr {$y +1}]
	}	
		close $fileId
	animate delete all
	set x [expr {$x + 1}]

}

quit

