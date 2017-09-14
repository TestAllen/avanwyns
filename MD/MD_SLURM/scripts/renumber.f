C renumbers pdb files 
        integer test,atomnum,resint
        character*24 acrap,dcrap,segid,atomtype,restype
        character*24 rescrap, numcrap, nrescrap
        character*200 ifile
        real*8 x,y,z


C get input filename from command line and open it      
C output is to standard out
        call get_command_argument(1,ifile)
        open(unit=1,file=ifile,status='old')
        
        atomnum=1
        resint=1
        
        read(1,111,IOSTAT=test) acrap, numcrap, atomtype, restype, 
     $   segid, rescrap, x, y, z, dcrap

C skip lines that aren't ATOM entries        
        do while ( acrap .ne. "ATOM" )
                
          read(1,111,IOSTAT=test) acrap, numcrap, atomtype, restype,
     $     segid, rescrap, x, y, z, dcrap 
        
        end do

        nrescrap=rescrap

C print out until end of file is reached
        do while ( test==0 )

C only print out ATOM entries        
          if( acrap .eq. "ATOM" ) then
         
C when a new residue is reached, update residue index (resint)   
            if( nrescrap .ne. rescrap ) then    
              resint=resint+1
              rescrap=nrescrap  
            end if
            
            write(*,222) acrap, atomnum, atomtype, restype, segid,
     $       resint, x, y, z, dcrap
            atomnum=atomnum+1
          end if

        read(1,111,IOSTAT=test) acrap, numcrap, atomtype, restype,
     $   segid, nrescrap, x, y, z, dcrap
        end do

 111  format(A4,A7,1X,A4,1X,A3,1X,A1,A5,3X,F8.3,F8.3,F8.3,A24)
 222  format(A4,I7,1X,A4,1X,A3,1X,A1,I5,3X,F8.3,F8.3,F8.3,A24)
      close(unit=1)
      end

