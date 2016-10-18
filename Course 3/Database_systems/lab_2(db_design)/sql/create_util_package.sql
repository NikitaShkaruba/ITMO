create or replace package util as
  function computeEmployeeSalary(h_id number) return number;
  procedure printEmployeesSalaries;

  function computeDepartmentProfit(d_id number) return number;
  function computeDepartmentDealsAmount(d_id number) return number;
  procedure printDepartmentsProfit;
end util;
/


create or replace package body util as
  --- Salaries
  function computeEmployeeSalary(h_id number) return number is
    result salaries.salary%type;
  begin
    select salary into result from salaries where h_id = human_id;
    return result;
  exception
    when NO_DATA_FOUND then
    return NULL;
  end;

  procedure printEmployeesSalaries as
  begin
    DBMS_OUTPUT.PUT_LINE('Salaries:');
    for person in (select * from people) loop
      DBMS_OUTPUT.PUT_LINE(person.surname || ' ' || person.name || ': ' || util.computeEmployeeSalary(person.id));
    end loop;
  end;

  --- Departments
  function computeDepartmentProfit(d_id number) return number is
    result products.price%type;
  begin
    select sum(price) into result from products
    where products.vendor in ( select id from people where people.id in (select id from days where days.department_id = d_id) );
    return result;
  exception
    when NO_DATA_FOUND then
    return NULL;
  end;

  function computeDepartmentDealsAmount(d_id number) return number is
    result products.price%type;
  begin
    select count(price) into result from products
    where products.vendor in ( select id from people where people.id in (select id from days where days.department_id = d_id) );
    return result;
  exception
    when NO_DATA_FOUND then
    return NULL;
  end;


  procedure printDepartmentsProfit as
  begin
    DBMS_OUTPUT.PUT_LINE('Salaries:');
    for department in (select * from departments) loop
      DBMS_OUTPUT.PUT_LINE( department.NAME || ' ### Deals: ' || util.computeDepartmentDealsAmount(department.id) || '. Profit: ' || util.computeDepartmentProfit(department.id));
    end loop;
  end;
end util;
/
