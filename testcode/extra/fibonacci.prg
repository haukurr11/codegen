program example;
var result : integer;

function fibonacci(n:integer):integer;
var firstval:integer;
var secondval:integer;
begin
    fibonacci := 0;
    if (n=1) or (n=2) then
        fibonacci:= 1
    else begin
        firstval := fibonacci(n-1);
        secondval := fibonacci(n-2);
        fibonacci := firstval + secondval
    end
end;

begin
  result := fibonacci(20);
  writeln(result)
end.
