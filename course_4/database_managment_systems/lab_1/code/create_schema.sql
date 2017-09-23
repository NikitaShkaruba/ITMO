set serveroutput on;

-- Lab function
CREATE OR REPLACE PROCEDURE show_nested_functions (cur_proc_name varchar, recursion_depth_char varchar DEFAULT '--') AS
BEGIN
  DBMS_OUTPUT.PUT_LINE(recursion_depth_char || ' ' || cur_proc_name);

  FOR row IN (SELECT referenced_name FROM user_dependencies WHERE (referenced_type = 'PROCEDURE' OR referenced_type = 'FUNCTION') AND name = cur_proc_name)
  LOOP
    show_nested_functions(row.referenced_name, recursion_depth_char || ' ' || SUBSTR(recursion_depth_char,1,2));
  END LOOP;
END;
/

-- Procedures to test with
CREATE OR REPLACE FUNCTION my_minimum(v1 number, v2 number) RETURN number IS
BEGIN
  IF v1 < v2 THEN
    RETURN v1;
  ELSE
    RETURN v2;
  END IF;
END;
/

CREATE OR REPLACE PROCEDURE proc_j
IS
BEGIN
  DBMS_OUTPUT.PUT_LINE('j');
END;
/

CREATE OR REPLACE PROCEDURE proc_h
IS
BEGIN
  DBMS_OUTPUT.PUT_LINE('h');
  DBMS_OUTPUT.PUT_LINE(my_minimum(1,2));
END;
/

CREATE OR REPLACE PROCEDURE proc_d
IS
BEGIN
  DBMS_OUTPUT.PUT_LINE('d');
END;
/

CREATE OR REPLACE PROCEDURE proc_f
IS
BEGIN
  DBMS_OUTPUT.PUT_LINE('f');
END;
/

CREATE OR REPLACE PROCEDURE proc_e
IS
BEGIN
  DBMS_OUTPUT.PUT_LINE('e');
  proc_j;
  proc_h;
END;
/

CREATE OR REPLACE PROCEDURE proc_c
IS
BEGIN
  DBMS_OUTPUT.PUT_LINE('c');
  proc_e;
  proc_f;
END;
/

CREATE OR REPLACE PROCEDURE proc_a
IS
BEGIN
  DBMS_OUTPUT.PUT_LINE('A');
  proc_c;
  proc_d;
END;
/

