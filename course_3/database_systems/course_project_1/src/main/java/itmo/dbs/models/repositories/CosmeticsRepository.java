package itmo.dbs.models.repositories;

import itmo.dbs.models.Cosmetic;
import org.springframework.data.repository.CrudRepository;

public interface CosmeticsRepository extends CrudRepository<Cosmetic, Long> { }
