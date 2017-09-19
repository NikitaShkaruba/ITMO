create table trigger_test (id integer);

create table triggerless_test (col1 integer, col2 integer);

create or replace trigger trigger_test_insert
before insert on trigger_test for each row
begin
  DBMS_OUTPUT.PUT_LINE('test');
end;
/
