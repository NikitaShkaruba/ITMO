package itmo.dbs.models.repositories;

import itmo.dbs.models.Cosmetic;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface CosmeticRepository extends CrudRepository<Cosmetic, Long> {}
