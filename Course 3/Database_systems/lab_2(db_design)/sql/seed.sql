DECLARE
  nikita_id number;
  vika_id number;
  programmers_department_id number;
  programmer_job_id number;
begin
  insert into people values(1, 'Shkaruba', 'Nikita', 'Eugenievich', TO_DATE('17-05-1996', 'dd-mm-yyyy'), 'M', NULL, NULL, 79819584408);
  insert into people values(2, 'Sukhanova', 'Victoria', 'Aleksandrovna', TO_DATE('30-11-1994', 'dd-mm-yyyy'), 'F', NULL, NULL, 79112489674);

  insert into jobs values(1, 'Programmer', 50000, 200000);
  insert into jobs values(1, 'Toilet cleaner', 10000, 20000);

  insert into departments values(1, 'Programmers department');
  insert into departments values(1, 'Cleaners department');

  --- 'rownum = 1' is needed so we can run seed.sql many times without cleaning
  select id into nikita_id from people where name = 'Nikita' and rownum = 1;
  select id into vika_id from people where name = 'Victoria' and rownum = 1;
  select id into programmers_department_id from departments where name = 'Programmers department' and rownum = 1;
  select id into programmer_job_id from jobs where name = 'Programmer' and rownum = 1;
  --- For the test purposes
  DBMS_OUTPUT.PUT_LINE('nikita_id: ' || nikita_id || ' vika_id:' || vika_id || ' programmers_department_id:' || programmers_department_id || ' programmer_job_id:' || programmer_job_id);

  insert into salaries values(1, nikita_id, programmers_department_id, programmer_job_id, 100005);
  insert into salaries values(2, vika_id, programmers_department_id, programmer_job_id, 100000);

  insert into days values(1, nikita_id, programmers_department_id, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    'Выносил мусор, задержался дома',
    NULL, NULL, NULL, NULL, NULL, NULL);
  insert into days values(2, vika_id, programmers_department_id, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    'Котик заболел',
    NULL, NULL, NULL, NULL, NULL, NULL);

  insert into products values(1, 'laptop', 2, nikita_id, TO_DATE('17-05-2014', 'dd-mm-yyyy'), 15500);
  insert into products values(2, 'teddy-bear', 23, vika_id, TO_DATE('30-11-2013', 'dd-mm-yyyy'), 7000);
  insert into products values(3, 'bubble', 15, vika_id, TO_DATE('11-03-2015', 'dd-mm-yyyy'), 77);
  insert into products values(4, 'bag', 3, nikita_id, TO_DATE('19-02-2012', 'dd-mm-yyyy'), 3590);
  insert into products values(5, 'book', 5, vika_id, TO_DATE('23-07-2015', 'dd-mm-yyyy'), 799);
  insert into products values(6, 'clock', 9, nikita_id, TO_DATE('24-08-2016', 'dd-mm-yyyy'), 1300);
  insert into products values(7, 'pillow', 15, vika_id, TO_DATE('09-09-2015', 'dd-mm-yyyy'), 950);
end;