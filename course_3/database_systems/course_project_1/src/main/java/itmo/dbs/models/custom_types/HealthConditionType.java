package itmo.dbs.models.custom_types;

import org.hibernate.HibernateException;
import org.hibernate.engine.spi.SessionImplementor;
import org.hibernate.type.BigDecimalType;
import org.hibernate.type.LongType;
import org.hibernate.usertype.UserType;
import org.springframework.util.ObjectUtils;
import java.io.Serializable;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;

public class HealthConditionType implements UserType {
    @Override
    public int[] sqlTypes() {
        return new int[] { Types.BIGINT };
    }

    @Override
    public Class returnedClass() {
        return HealthCondition.class;
    }

    @Override
    public Object nullSafeGet(ResultSet rs, String[] names, SessionImplementor session, Object owner) throws HibernateException, SQLException {
        HealthCondition healthCondition = null;

        if (!rs.wasNull()) {
            long happiness = LongType.INSTANCE.nullSafeGet(rs, names[0], session);
            long hungriness = LongType.INSTANCE.nullSafeGet(rs, names[1], session);
            long cleanliness = LongType.INSTANCE.nullSafeGet(rs, names[2], session);

            healthCondition = new HealthCondition(happiness, hungriness, cleanliness);
        }
        return healthCondition;
    }

    @Override
    public void nullSafeSet(PreparedStatement st, Object value, int index, SessionImplementor session) throws HibernateException, SQLException {
        if (value == null) {
            st.setNull(index, BigDecimalType.INSTANCE.sqlType());
            st.setNull(index + 1, BigDecimalType.INSTANCE.sqlType());
            st.setNull(index + 2, BigDecimalType.INSTANCE.sqlType());
        } else {
            final HealthCondition healthCondition = (HealthCondition) value;
            st.setLong(index, healthCondition.happiness);
            st.setLong(index + 1, healthCondition.hungriness);
            st.setLong(index + 2, healthCondition.cleanliness);
        }
    }

    // Default implementation
    @Override
    public boolean isMutable() {
        return false;
    }

    @Override
    public boolean equals(Object x, Object y) throws HibernateException {
        return ObjectUtils.nullSafeEquals(x, y);
    }

    @Override
    public int hashCode(Object x) throws HibernateException {
        assert (x != null);
        return x.hashCode();
    }

    @Override
    public Object deepCopy(Object value) throws HibernateException {
        return value;
    }

    @Override
    public Object replace(Object original, Object target, Object owner)
            throws HibernateException {
        return original;
    }

    @Override
    public Serializable disassemble(Object value) throws HibernateException {
        return (Serializable) value;
    }

    @Override
    public Object assemble(Serializable cached, Object owner)
            throws HibernateException {
        return cached;
    }
}
