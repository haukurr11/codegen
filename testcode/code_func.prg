program test;
var
  x,y : integer;


function add(x:integer; y:integer):integer;
begin
	add := x + y
end;

function mult(x:integer; y:integer):integer;
begin
	mult := x * y
end;

procedure toScreen(x:integer);
var y: integer;
	
begin
	y := x;
	writeln(y)
end;

begin
   x := 3;
   toScreen(x);
   x := add(x,2);
   toScreen(x);
   x := mult(x,3);
   toScreen(x)
end.
