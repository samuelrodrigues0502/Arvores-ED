package agm;

import java.util.Objects;

public class Adjacencia {
	
    public int origem;
    public int destino;
    public int peso;

    public Adjacencia(int origem, int destino, int peso) {
        this.origem = origem;
        this.destino = destino;
        this.peso = peso;
    }
    
    

    @Override
	public int hashCode() {
		return Objects.hash(destino, origem, peso);
	}



	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Adjacencia other = (Adjacencia) obj;
		return destino == other.destino && origem == other.origem && peso == other.peso;
	}



	@Override
    public String toString() {
        return this.origem +" -> "+this.destino +" = "+this.peso;
    }
    
    
}