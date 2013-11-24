program example;
var i,j : integer;

begin
    i := 0;
    j := 6;
    if (i = 0) or (j > 6) then
      j := 1337
    else
      j := -1;
    if not(j = 1336) then
      j := j + 1
    else
      j := 0;
    if (j <> 0) then
      j := j + 2
    else
      j := 1;
    if (j <= 1339 ) then
      j := 2
    else
      j := (j+5)/2;
    if (j >= 600) then
      j := j * 8 
    else
      j := 3;
    writeln(j)
end.
