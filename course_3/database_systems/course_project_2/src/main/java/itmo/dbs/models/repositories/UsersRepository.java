package itmo.dbs.models.repositories;

import itmo.dbs.models.User;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface UsersRepository extends MongoRepository<User, String> {}
