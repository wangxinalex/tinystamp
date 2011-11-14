#!/usr/bin/perl

sub parseLog
{
    my $file = shift;
    my $sum = 0;
    my $average = 0;
    my @durations;

    # Open file
    open(FILEHANDLER, $file );
    while (<FILEHANDLER>) 
    {
		# Parsing time (depending on benchmark)
		# bayes "Learn time = 0.014401"
		# genome "Time = 0.008518"
		# intruder "Elapsed time    = 0.025493 seconds"
		# kmeans "Time: 0.0317872 seconds"
		# labyrinth "Elapsed time    = 0.025085 seconds"
		# ssca2 "Time taken for all is  0.062565 sec."
		# vacation "Time = 0.047641"
		# yada "Elapsed time                    = 0.081"

		if ( /^Learn time = (\d*\.\d*)/  ) {
		    push( @durations, $1 );
		} elsif ( /^Time\s*=\s*(\d*\.\d*).*/ ) {
		    push( @durations, $1 );
		} elsif ( /^Elapsed time\s*=\s*(\d*\.\d*).*/ ) {
		    push( @durations, $1 );
		} elsif ( /^Time\s*:\s*(\d*\.\d*).*/ ) {
		    push( @durations, $1 );
		} elsif ( /^Time taken for all is (\d*\.\d*).*/ ) {
		    push( @durations, $1 );
		} 
    }
    close(FILEHANDLER);

    if( scalar @durations == 0 ){
		print "Error parsing $file\n";
		return 0;
    }

    # Calculate average
    $sum = 0;
    foreach $duration (@durations) {
		$sum += $duration;
    }
    $average = $sum / scalar @durations;

    # Calcualte Variance and Standard deviation
    $dev = 0;
    foreach $duration (@durations) {
		$dev += ($duration - $average) * ($duration - $average);
    }
    $stddev = sqrt ($dev / ((scalar @durations) - 1));
    print "$file has a std dev of $stddev\n";

    return ($average, $stddev);

#    # Remove extreme values for 20%
#    for( $i = 0 ; $i < int(scalar @durations / 5) ; $i++ ) {
#      my $extreme = 0;
#      my $to_remove;
#      # Find max deviation
#      foreach $duration (@durations) {
#	  	# Add it to extreme
#		  my $diff = $duration - $average;
#		  if( $diff < 0 ) {
#		      $diff = 0 - $diff;
#		  }
#		  if( $extreme < $diff ) {
#		      $extreme = $diff;
#		      $to_remove = $duration;
#		  }
#      }
#      # Create new array without max value
#      my @new_durations;
#      foreach $duration (@durations) {
#		  if( $duration != $extreme ) {
#		      push( @new_durations, $duration );
#		  }
#      }
      # Set new into durations
#      @durations = @new_duration;
#    }

#    # Recalculate average after removing extreme values
#    $sum = 0;
#    foreach $duration (@durations) {
#	$sum += $duration;
#    }
#    $average = $sum / scalar @durations;
#
#    return $average;
}

sub parseLogStats
{
    my $file = shift;

    my $sum = 0;
    my $average_com = 0;
    my $average_abo = 0;

    my $duration;
    my @commits;
    my @aborts;

    # Open file
    open(FILEHANDLER, $file );
    while (<FILEHANDLER>) 
    {
		# Parsing time (depending on benchmark)
		# bayes "Learn time = 0.014401"
		# genome "Time = 0.008518"
		# intruder "Elapsed time    = 0.025493 seconds"
		# kmeans "Time: 0.0317872 seconds"
		# labyrinth "Elapsed time    = 0.025085 seconds"
		# ssca2 "Time taken for all is  0.062565 sec."
		# vacation "Time = 0.047641"
		# yada "Elapsed time                    = 0.081"
	
		if ( /^Learn time = (\d*\.\d*)/  ) {
		    $duration = $1;
		} elsif ( /^Time\s*=\s*(\d*\.\d*).*/ ) {
		    $duration = $1;
		} elsif ( /^Elapsed time\s*=\s*(\d*\.\d*).*/ ) {
		    $duration = $1;
		} elsif ( /^Time\s*:\s*(\d*\.\d*).*/ ) {
		    $duration = $1;
		} elsif ( /^Time taken for all is (\d*\.\d*).*/ ) {
		    $duration = $1;
		} 
	
		if ( /commits    : (\d+)/  ) {
		    push( @commits , $1 / $duration );
		}
		if ( /aborts     : (\d+)/  ) {
		    push( @aborts, $1 / $duration );
		}
    }
    close(FILEHANDLER);

    if( scalar @commits == 0 ) {
		print "Error parsing $file\n";
		return 0;
    }

    # Calculate average
    $sum = 0;
    foreach $duration (@commits) {
		$sum += $duration;
    }
    $average_com = $sum / scalar @commits;

    # Calculate average
    $sum = 0;
    foreach $duration (@aborts) {
		$sum += $duration;
    }
    $average_abo = $sum / scalar @aborts;

    return $average_com." ".$average_abo;
}



sub createPlot
{
    my $dir = shift;
	$_ = $dir;
    s/\//./;
    # Create gp file
    open( GP_FILE, "|gnuplot" );
	my $errorbars=1;
	print GP_FILE "reset
		set size 1.6, 1.6
		set term postscript eps enhanced color 22
		set output \"$dir/graph.$_.eps\"
		set title \"$_\"
		set key outside bottom
		set key right
		set multiplot
		set x2range [0:60]
		set xrange [0:60]
		set grid xtics lt 1 lw 2 lc rgb \"#444444\"
		set xlabel \"amount of threads\"
		set ylabel \"Scalability\"
		set x2tics
		plot ";
    opendir S, "$dir/";
    my @datafiles = grep( /.\.data/, readdir( S ) );
    $index = 1;
    foreach $datafile (@datafiles) {
		next if $datafile eq "." or $datafile eq ".." or -d $dir."/".$datafile or !($datafile =~ /.\.data/);
			if($errorbars==1) {
				print GP_FILE "\"$dir/$datafile\" using 1:4:5 title \"$datafile\" with lines, \"$dir/$datafile\" using 1:4:5 title \"standard deviation\" with yerrorbars";
			}
			else {
				print GP_FILE "\"$dir/$datafile\" using 1:4:5 title \"$datafile\" with lines";
			}
		if( $index != scalar(@datafiles) ) {
		    print GP_FILE ", ";
		}
		$index++;
    }
    closedir S;

	print GP_FILE 
		"\nunset grid
		set xlabel \" \"
		set ylabel \" \"
		set xtics format \" \"
		set x2tics 1
		set x2tics format \" \"
		set grid x2tics lt 0 lw 1 lc rgb \"#338888\"
		plot ";
	    opendir S, "$dir/";
		my @datafiles = grep( /.\.data/, readdir( S ) );
		$index = 1;
		foreach $datafile (@datafiles) {
		    next if $datafile eq "." or $datafile eq ".." or -d $dir."/".$datafile or !($datafile =~ /.\.data/);
				if($errorbars==1) {
				    print GP_FILE "\"$dir/$datafile\" using 1:4:5 title \"$datafile\" with lines, \"$dir/$datafile\" using 1:4:5 title \"standard deviation\" with yerrorbars";
				}
				else {
				    print GP_FILE "\"$dir/$datafile\" using 1:4:5 title \"$datafile\" with lines";
				}
		    if( $index != scalar(@datafiles) ) {
		        print GP_FILE ", ";
		    }
		    $index++;
	    }
	    closedir S;

		print GP_FILE "\nunset multiplot\n";
    
    print GP_FILE "\n exit \n";

    close( GP_FILE );

    # Execute gnuplot
    #$cur = getcwd;
    #chdir( $dir );
    #system( "gnuplot", "graph.gp" );
    #chdir( $cur );

}

sub createPlotStats
{
    my $dir = shift;
    my $stats = shift;
    my $stats_index = 2;

    if( $stats eq "aborts" ){
		$stats_index = 3;
    }

    # TODO generate one graph for each column

    # Generate GNU Plot file

    # Create gp file
    open( GP_FILE, "|gnuplot" );
	$_ = $dir;
	s/\//./;
    print GP_FILE 
	"set size 1.6, 1.6
    set term postscript eps enhanced color 22
    set output \"$dir/graph_$stats.$_.eps\"
    set title \"$_\"
    set key outside bottom
    set key right
	set multiplot
	set x2range [0:60]
	set xrange [0:60]
    set xtics 10
	set grid xtics lt 1 lw 2 lc rgb \"#444444\"
    set xlabel \"amount of threads\"
	set ylabel \"$stats\"
	set x2tics
    plot ";

    opendir S, "$dir/";
    my @datafiles = grep( /.\.sdata/, readdir( S ) );

    $index = 1;
    foreach $datafile (@datafiles) {
		next if $datafile eq "." or $datafile eq ".." or -d $dir."/".$datafile or !($datafile =~ /.\.sdata/);

		print GP_FILE "\"$dir/$datafile\" using 1:$stats_index title \"$datafile\" with lines";
		if( $index != scalar(@datafiles) ) {
		    print GP_FILE ", ";
		}
		$index++;
    }
	print GP_FILE 
	"\nunset grid
	set xlabel \" \"
	set ylabel \" \"
	set xtics format \" \"
	set x2tics 1
	set x2tics format \" \"
	set grid x2tics lt 0 lw 1 lc rgb \"#338888\"
    plot ";

	$index = 1;
	foreach $datafile (@datafiles) {
		next if $datafile eq "." or $datafile eq ".." or -d $dir."/".$datafile or !($datafile =~ /.\.sdata/);
		print GP_FILE "\"$dir/$datafile\" using 1:$stats_index title \"$datafile\" with lines";
		if( $index != scalar(@datafiles) ) {
			print GP_FILE ", ";
		}
		$index++;
	}

    closedir S;
    print GP_FILE "\n exit \n";
    close( GP_FILE );

    # Execute gnuplot
    #$cur = getcwd;
    #chdir( $dir );
    #system( "gnuplot", "graph.gp" );
    #chdir( $cur );
}




$i = 0;
foreach $argnum (0 .. $#ARGV) {
    @logdirs[$i] = $ARGV[$argnum];
    $i++;
}

foreach $logdir (@logdirs) {
	my %results;
	opendir R, $logdir;

	# Sort files (without . and ..)
	@logfiles=sort grep (!/^\.\.?$/, readdir (R));
	my $standardDev=0;

	# Parse log files
	foreach $logfile (@logfiles) {
		next if $logfile eq "." or $logfile eq ".." or -d $logdir."/".$logfile or !($logfile =~ /.log/);

		# Parsing log files which matche
		if( $logfile =~ /(.*)\.(\d+)\.log/ ){
		    $name   = $1;
		    $thread = sprintf( "%03d" ,int($2)); # TODO Use a sprintf %03d
			($results{ $name }{ $thread }, $standardDev{ $name }{ $thread } ) = parseLog( "$logdir/$logfile" );
		}
	}
	
	closedir R;

	# Calculate speedup and writing to file
	for my $stm ( sort keys %results ) {
	    next if $stm =~ /seq/;

	    # Creating data file
	    open (MYFILE, ">".$logdir."/".$stm.'.data');
	
	    # Creating fields label
	    print MYFILE "#Thread Time RatioSTM RatioSeq StandardDev\n";

	    #TODO Must ensure order of thread
#	    my @sorted= grep {s/(^|\D)0+(\d)/$1$2/g,1} sort
#	    grep {s/(\d+)/sprintf"%06.6d",$1/ge,1} keys %{%{%results->{ $stm }->{ $bench }}};

	    for my $thread ( sort keys %{ %results->{$stm} } ) {
			# Seq and stm ratio
			my $ratio_stm = 0;
			my $ratio_seq = 0;
			# Get sequential time and stm time for 1 thread
			my $seq1 = $results{ 'seq' }{ "001" };
			my $stm1 = $results{ $stm }{ '001' };
			# Get time for current thread
			my $time = $results{ $stm }{ $thread };

			# Calculate ratio if we can
			if( $seq1 && $time != 0 ) {
			    $ratio_seq = $seq1 / $results{ $stm }{ $thread };
		}
		if( $stm1 && $time != 0 ) {
		    $ratio_stm = $stm1 / $results{ $stm }{ $thread };
		}

		# Writing to file
		print MYFILE "$thread $time $ratio_stm $ratio_seq $standardDev{ $stm }{ $thread }\n";

	    }
	    
	    # Save and close data file
	    close( MYFILE );
	}

	# Create plots
	createPlot( $logdir );

}


#exit;


#TODO Per sec is not usefull because we can do it in gnuplot ... plot ... 1:($2/$3)
#     But make sure that calculus is ok

#create stats data
foreach $logdir (@logdirs) {
	my %results;
	opendir R, $logdir;

	# Sort files (without . and ..)
	@logfiles=sort grep (!/^\.\.?$/, readdir (R));

	# Parse log files
	foreach $logfile (@logfiles) {
		next if $logfile eq "." or $logfile eq ".." or -d $logdir."/".$logfile or !($logfile =~ /.log/);
		next if $logfile =~ /seq/;

		# Parsing log files which matche
		if( $logfile =~ /(.*)\.(\d+)\.log/ ){
		    $name   = $1;
		    $thread = sprintf( "%03d" ,int($2)); # TODO Use a sprintf %03d
		    $results{ $name }{ $thread } = parseLogStats( "$logdir/$logfile" );
		}
	}
	
	closedir R;

#jbs debug
#for my $stm ( sort keys %results ) {
#	next if $stm =~ /seq/;
#	print $stm, "\n";
#}
#jbs debug end

	# Calculate speedup and writing to file
	for my $stm ( sort keys %results ) {
	    next if $stm =~ /seq/;

	    # Creating data file
	    open (MYFILE, ">".$logdir."/".$stm.'.sdata');

	    # Creating fields label
	    print MYFILE "#Thread Commits/sec Aborts/sec\n";

	    #TODO Must ensure order of thread
#	    my @sorted= grep {s/(^|\D)0+(\d)/$1$2/g,1} sort
#	    grep {s/(\d+)/sprintf"%06.6d",$1/ge,1} keys %{%{%results->{ $stm }->{ $bench }}};

	    for my $thread ( sort keys %{ %results->{$stm} } ) {
		# Get data
		my $time = $results{ $stm }{ $thread };

		# Writing to file
		print MYFILE "$thread $time\n";

	    }
	    
	    # Save and close data file
	    close( MYFILE );
	}

	# Create plots
	createPlotStats( $logdir, "commits_per_sec" );
	createPlotStats( $logdir, "aborts_per_sec" );
}

