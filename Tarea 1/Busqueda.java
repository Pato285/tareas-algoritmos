import java.io.*;
class Busqueda{
	static public void main(String[]args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    String texto="";
    System.out.print("Ingrese nombre de archivo: ")
		String archivo=br.readLine();
    System.out.print("Ingrese patron a buscar: ")
		String patron=br.readLine();
		BufferedReader t = new BufferedReader(new InputStreamReader(new FileInputStream(archivo), "ISO-8859-1"));
		String linea;
		while((linea=t.readLine())!=null){
			texto=texto.concat(linea);
		}
		t.close();
		int m=patron.length();
		int n=texto.length();
		long t0,t1;

		//////////////////////////////////////
		System.out.println("Fuerza bruta\nSe econtro coincidencia en las pociciones:");
		t0=System.currentTimeMillis();

		for(int i=0; i<n+1-m; i++){
			for(int j=0;j<m;j++){
				if(texto.charAt(i+j)!=patron.charAt(j))break;
				if(j==m-1) System.out.print((i+1)+",");
			}
		}

		t1=System.currentTimeMillis();
		System.out.println(" Tardando " + (t1-t0) + " milisegundos\n");
		/////////////////////////////////////
		System.out.println("Knuth-Morris-Pratt\nSe econtro coincidencia en las pociciones:");
		t0=System.currentTimeMillis();

		int []f=new int[m];
		f[0]=0;
		int j=0;
		int i;
		while(j<m){
			i=f[j];
			while(i>0 && patron.charAt(i)!=patron.charAt(j)){
				i=f[i];
			}
			if(patron.charAt(i)==patron.charAt(j)){
				f[j]=i;
			}
			else{
				f[j]=0;
			}
			j++;
		}
		i=0;
		j=0;
		while(i<n){
			while(j>0 && texto.charAt(i)!=patron.charAt(j)){
				j=f[j];
			}
			if (texto.charAt(i)==patron.charAt(j)){
				j++;
			}
			if(j==m){
				i=i-j+1;
				System.out.print((i+1)+",");
				j=0;
			}
			i++;
		}

		t1=System.currentTimeMillis();
		System.out.println(" Tardando " + (t1-t0) + " milisegundos\n");
		/////////////////////////////////////
		System.out.println("Boyer-Moore-Horspool\nSe econtro coincidencia en las pociciones:");
		t0=System.currentTimeMillis();
		String patron2=" ".concat(patron);
		texto=" ".concat(texto);
		i=m;
		j=m;
		while(i<=n){
			if (j==0){
				System.out.print((i-m+1)+",");
				j=m;
				i++;
			}
			else if(texto.charAt(i-(m-j))==patron2.charAt(j)){
				j--;
			}
			else{
				i=i+(m-patron.lastIndexOf(texto.charAt(i))+1);
				j=m;
			}

		}


		t1=System.currentTimeMillis();
		System.out.println(" Tardando " + (t1-t0) + " milisegundos\n");
		////////////////////////////////////
	}
}
