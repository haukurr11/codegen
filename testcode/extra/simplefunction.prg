program example;

function fibonacci(n:integer):integer;
begin
	fibonacci:= fibonacci(n-1);
end;

begin
        i := 1;
        j := 2;
	  writeln(i+j)
end.
