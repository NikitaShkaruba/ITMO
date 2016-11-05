package itmo.dbs.models.repositories;

import itmo.dbs.models.User;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface UsersRepository extends CrudRepository<User, Long> {}
