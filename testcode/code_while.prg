program example;
var i : integer;
var j : integer;

begin
	i := 0;
	j := 1;
	while (i<10) do begin
		j := (i +  j);
		i := i + 1
	end;
	writeln(i);
	writeln(j)
end.
