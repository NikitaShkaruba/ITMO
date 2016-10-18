create table people (
    id number constraint people_pk primary key not null,
    surname varchar(255) not null,
    name varchar(255) not null,
    patronymic varchar(255),
    birth_day date not null,
    gender char(1) not null,
    birth_place varchar(255) not null,
    address varchar(255),
    phone number(11) not null
);

create table jobs (
  id number constraint jobs_pk primary key not null,
  min_salary number not null,
  max_salary number not null
);

create table departments (
  id number constraint departments_pk primary key not null,
  name varchar(255) not null
);

create table salaries (
  id number constraint salaries_pk primary key not null,
  human_id number not null,
  CONSTRAINT salaries_human_fk FOREIGN KEY (human_id) REFERENCES people(id),
  department_id number not null,
  CONSTRAINT salaries_department_fk FOREIGN KEY (human_id) REFERENCES departments(id),
  job_id number not null,
  CONSTRAINT salaries_job_fk FOREIGN KEY (human_id) REFERENCES jobs(id),
  salary number not null
);

--- Days
--- day_n is a short comment about why this day was passed, or it's null if it was working day
create table days (
    id number constraint days_pk primary key not null,
    human_id number not null,
    CONSTRAINT days_human_fk FOREIGN KEY (human_id) REFERENCES people(id),
    department_id number not null,
    CONSTRAINT days_department_fk FOREIGN KEY (department_id) REFERENCES departments(id),
    day_1 varchar(255),
    day_2 varchar(255),
    day_3 varchar(255),
    day_4 varchar(255),
    day_5 varchar(255),
    day_6 varchar(255),
    day_7 varchar(255),
    day_8 varchar(255),
    day_9 varchar(255),
    day_10 varchar(255),
    day_11 varchar(255),
    day_12 varchar(255),
    day_13 varchar(255),
    day_14 varchar(255),
    day_15 varchar(255),
    day_16 varchar(255),
    day_17 varchar(255),
    day_18 varchar(255),
    day_19 varchar(255),
    day_20 varchar(255),
    day_21 varchar(255),
    day_22 varchar(255),
    day_23 varchar(255),
    day_24 varchar(255),
    day_25 varchar(255),
    day_26 varchar(255),
    day_27 varchar(255),
    day_28 varchar(255),
    day_29 varchar(255),
    day_30 varchar(255)
);

--- Products
create table products (
  id_product number constraint products_pk primary key not null,
  name varchar(255) not null,
  amount number not null,
  vendor number not null,
  CONSTRAINT products_fk FOREIGN KEY (vendor) REFERENCES people(id),
  date_when date not null,
  price number not null
);
