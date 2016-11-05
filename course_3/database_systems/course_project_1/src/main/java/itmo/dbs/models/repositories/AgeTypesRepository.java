package itmo.dbs.models.repositories;

import itmo.dbs.models.AgeType;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource(collectionResourceRel = "age_types", path = "age_types")
public interface AgeTypesRepository extends CrudRepository<AgeType, Long> {}
