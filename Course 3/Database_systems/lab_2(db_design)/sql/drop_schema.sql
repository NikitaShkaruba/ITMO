--- Drop tables
drop table people cascade constraints purge;
drop table jobs cascade constraints purge;
drop table departments cascade constraints purge;
drop table salaries cascade constraints purge;
drop table days cascade constraints purge;
drop table products cascade constraints purge;

--- Drop sequences
drop sequence people_id_seq;
drop sequence job_id_seq;
drop sequence department_id_seq;
drop sequence salary_id_seq;
drop sequence days_id_seq;
drop sequence products_id_seq;
