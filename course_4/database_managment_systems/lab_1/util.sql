select trigger_name from all_triggers where table_name = 'TRIGGER_TEST';
select table_name from all_triggers where trigger_name = 'TRIGGER_TEST_INSERT';
