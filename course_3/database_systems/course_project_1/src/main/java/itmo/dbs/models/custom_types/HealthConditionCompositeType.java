package itmo.dbs.models.custom_types;

import org.hibernate.HibernateException;
import org.hibernate.engine.spi.SessionImplementor;
import org.hibernate.type.BigDecimalType;
import org.hibernate.type.Type;
import org.hibernate.usertype.CompositeUserType;
import org.springframework.util.ObjectUtils;
import java.io.Serializable;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class HealthConditionCompositeType implements CompositeUserType {
    @Override
    public String[] getPropertyNames() {
        return new String[] { "HAPPINESS", "HUNGRINESS", "CLEANLINESS" };
    }

    @Override
    public Type[] getPropertyTypes() {
        return new Type[] { BigDecimalType.INSTANCE, BigDecimalType.INSTANCE, BigDecimalType.INSTANCE };
    }

    @Override
    public Object getPropertyValue(Object component, int property) throws HibernateException {
        HealthCondition healthCondition = (HealthCondition) component;

        switch(property) {
            case 0: return healthCondition.happiness;
            case 1: return healthCondition.hungriness;
            case 2: return healthCondition.cleanliness;
            default: return null;
        }
    }

    @Override
    public void setPropertyValue(Object component, int property, Object value) throws HibernateException {
        HealthCondition healthCondition = (HealthCondition) component;

        switch(property) {
            case 0:
                healthCondition.happiness = (long) value;
                break;
            case 1:
                healthCondition.hungriness = (long) value;
                break;
            case 2:
                healthCondition.cleanliness = (long) value;
                break;
        }
    }

    @SuppressWarnings("rawtypes")
    @Override
    public Class returnedClass() {
        return HealthCondition.class;
    }

    @Override
    public Object nullSafeGet(ResultSet rs, String[] names, SessionImplementor session, Object owner) throws HibernateException, SQLException {
        HealthCondition healthCondition = null;

        if (!rs.wasNull()) {
            healthCondition = new HealthCondition(rs.getLong(names[0]), rs.getLong(names[1]), rs.getLong(names[2]));
        }
        return healthCondition;
    }

    @Override
    public void nullSafeSet(PreparedStatement st, Object value, int index, SessionImplementor session) throws HibernateException, SQLException {
        if (value == null) {
            st.setNull(index, BigDecimalType.INSTANCE.sqlType());
            st.setNull(index + 1, BigDecimalType.INSTANCE.sqlType());
            st.setNull(index, BigDecimalType.INSTANCE.sqlType());
        } else {
            final HealthCondition healthCondition = (HealthCondition) value;
            st.setLong(index, healthCondition.happiness);
            st.setLong(index, healthCondition.hungriness);
            st.setLong(index, healthCondition.cleanliness);
        }
    }

    @Override
    public Serializable disassemble(Object value, SessionImplementor session) throws HibernateException {
        return (Serializable) value;
    }

    @Override
    public Object assemble(Serializable cached, SessionImplementor session, Object owner) throws HibernateException {
        return cached;
    }

    @Override
    public Object replace(Object original, Object target, SessionImplementor session, Object owner) throws HibernateException {
        return this.deepCopy(original);
    }


    /* Default implementation*/
    @Override
    public Object deepCopy(Object value) throws HibernateException {
        return value;
    }

    @Override
    public boolean isMutable() {
        return true;
    }

    @Override
    public boolean equals(Object x, Object y) throws HibernateException {
        return ObjectUtils.nullSafeEquals(x, y);
    }

    @Override
    public int hashCode(Object x) throws HibernateException {
        return x.hashCode();
    }
}
