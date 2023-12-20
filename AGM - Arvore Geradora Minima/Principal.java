package agm;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Principal {

    public static final int qtdVert = 8;

    public static void main(String[] args) {

        List<LinkedList<Integer>> listAdjacencia = new LinkedList<LinkedList<Integer>>();
        Scanner teclado = new Scanner(System.in);

        System.out.println("Lista de Adjacência");

        preencheLista(listAdjacencia);//Função que cria a lista de adjacencia
        for (int i = 0; i < listAdjacencia.size(); i++) {
            System.out.println(i + " -> " + listAdjacencia.get(i));
        }

        System.out.println("Defina o vértice de partida para a criação da AGM(0-7): ");
        int verticeOrigemAGM = teclado.nextInt();

        if (verticeOrigemAGM >= 0 && verticeOrigemAGM <= 7) {

            List<Integer> listT = new ArrayList<>();//Lista que auxilia na descisão do caminho da AGM.
                                                    //Contabiliza os vértices já passados.
            List<Integer> listFringe = new ArrayList<>();//Lista que pega e guarda as posíveis rotas a 
                                                         //partir do vértice localizado.
            List listAGM = new ArrayList<>();//Lista que define as ligações da AGM.

            listT.add(verticeOrigemAGM);
            removeDaListaAdj(listAdjacencia, verticeOrigemAGM);
            int pesoTotal = 0;

            while (listT.size() < qtdVert) {//Fica em loop enquanto todos os vértices não forem adicionados na listT.

                int ultimaPos = listT.get(listT.size() - 1);//pega o último vértice da lista para definir o menor caminho
                                                            //a partir dele.
                int menorPeso = 99999999;
                int verticeDestino = 0;
                
                //laço que contabiliza as possíveis rotas a partir de um vértice.
                for (int i = 0; i < listAdjacencia.get(ultimaPos).size(); i++) {
                    listFringe.add(listAdjacencia.get(ultimaPos).get(i));
                    listFringe.add(listAdjacencia.get(ultimaPos).get(i + 1));
                  //Usado para controle.
//                System.out.println("Franja:");
//                System.out.println(listFringe);

                    i++;
                }
                //laço que determina o menor caminho comparando os vértices contabilizados
                //na franja e seus respectivos pesos.
                for (int i = 0; i < listFringe.size(); i++) {
                    if (listFringe.get(i + 1) < menorPeso) {
                        menorPeso = listFringe.get(i + 1);
                        verticeDestino = listFringe.get(i);
                    }
                    i++;
                }

                //adiciona o vértice determinado como melhor destino na listT
                //caso o mesmo já não esteja lá.
                if (!(listT.contains(verticeDestino))) {
                    listT.add(verticeDestino);
                }
                
                //laço que remove da franja o vértice escolhido como destino e seu respectivo peso.
                while (listFringe.indexOf(verticeDestino) != -1) {
                    listFringe.remove(listFringe.indexOf(verticeDestino) + 1);
                    listFringe.remove(listFringe.indexOf(verticeDestino));
                }
                
              //Controle das variáveis.
//            System.out.println("Menor peso: " + menorPeso + " Vertice de destino: " + verticeDestino);
//
////            for (int i = 0; i < listAdjacencia.size(); i++) {
////                System.out.println(i + " -> " + listAdjacencia.get(i));
////            }
////
////            System.out.println("T:" + listT);

                //Função que pega a origem da rota escolhida a partir do seu destino e peso.
                //É utilizada exclusivamente para a construção da AGM.
                int origem = procuraOrigem(listAdjacencia, verticeDestino, menorPeso);
                removeDaListaAdj(listAdjacencia, verticeDestino);
                
                pesoTotal += menorPeso;//Soma os menores pesos.
                
                listAGM.add(origem + " -> " + verticeDestino + " Peso: " + menorPeso);

            }
            
            System.out.println("\nLigações grafo AGM");
            for (int i = 0; i < listAGM.size(); i++) {
                System.out.println(listAGM.get(i));
            }
            
            System.out.println("\nPeso total: " + pesoTotal);
        }else{
            System.out.println("Vértice inválido.");
        }

    }

    public static void preencheLista(List<LinkedList<Integer>> listAdjacencia) {

        for (int i = 0; i < qtdVert; i++) {
            listAdjacencia.add(new LinkedList<>());
        }//Cria uma lista para cada linha da lista de adjacencia.

        //Puxando função para criar vertices não direcionais.
        criaVertice(listAdjacencia, new Adjacencia(1, 2, 36));
        criaVertice(listAdjacencia, new Adjacencia(2, 1, 36));

        criaVertice(listAdjacencia, new Adjacencia(1, 3, 29));
        criaVertice(listAdjacencia, new Adjacencia(3, 1, 29));

        criaVertice(listAdjacencia, new Adjacencia(1, 5, 32));
        criaVertice(listAdjacencia, new Adjacencia(5, 1, 32));

        criaVertice(listAdjacencia, new Adjacencia(1, 7, 19));
        criaVertice(listAdjacencia, new Adjacencia(7, 1, 19));

        criaVertice(listAdjacencia, new Adjacencia(5, 4, 35));
        criaVertice(listAdjacencia, new Adjacencia(4, 5, 35));

        criaVertice(listAdjacencia, new Adjacencia(7, 4, 37));
        criaVertice(listAdjacencia, new Adjacencia(4, 7, 37));

        criaVertice(listAdjacencia, new Adjacencia(7, 5, 28));
        criaVertice(listAdjacencia, new Adjacencia(5, 7, 28));

        criaVertice(listAdjacencia, new Adjacencia(7, 0, 16));
        criaVertice(listAdjacencia, new Adjacencia(0, 7, 16));

        criaVertice(listAdjacencia, new Adjacencia(0, 4, 38));
        criaVertice(listAdjacencia, new Adjacencia(4, 0, 38));

        criaVertice(listAdjacencia, new Adjacencia(2, 3, 17));
        criaVertice(listAdjacencia, new Adjacencia(3, 2, 17));

        criaVertice(listAdjacencia, new Adjacencia(0, 2, 26));
        criaVertice(listAdjacencia, new Adjacencia(2, 0, 26));

        criaVertice(listAdjacencia, new Adjacencia(7, 2, 34));
        criaVertice(listAdjacencia, new Adjacencia(2, 7, 34));

        criaVertice(listAdjacencia, new Adjacencia(2, 6, 40));
        criaVertice(listAdjacencia, new Adjacencia(6, 2, 40));

        criaVertice(listAdjacencia, new Adjacencia(3, 6, 52));
        criaVertice(listAdjacencia, new Adjacencia(6, 3, 52));

        criaVertice(listAdjacencia, new Adjacencia(0, 6, 58));
        criaVertice(listAdjacencia, new Adjacencia(6, 0, 58));

        criaVertice(listAdjacencia, new Adjacencia(6, 4, 93));
        criaVertice(listAdjacencia, new Adjacencia(4, 6, 93));

    }

    public static void criaVertice(List<LinkedList<Integer>> listAdjacencia, Adjacencia adj) {
        
        //cria os vértices de acordo com a adjacencia passada(origem, destino, peso);
        listAdjacencia.get(adj.origem).add(adj.destino);
        listAdjacencia.get(adj.origem).add(adj.peso);

    }

    public static void removeDaListaAdj(List<LinkedList<Integer>> listAdjacencia, int vertice) {
        //Após a adição de um vértice na listaT ocorre a
        //remoção do vértice dos destinos dos vértices da lista de adjacencia.
        //para que o mesmo não seja mais incluido na possível menor rota.
        
        for (int i = 0; i < listAdjacencia.size(); i++) {

            int pos = listAdjacencia.get(i).indexOf(vertice);
            if (pos != -1) {
                listAdjacencia.get(i).remove(pos + 1);//exclusão do peso.
                listAdjacencia.get(i).remove(pos);//exclusão do indice do vértice.
            }
        }
    }

    public static int procuraOrigem(List<LinkedList<Integer>> listAdjacencia, int destino, int peso) {
        
        //Função que auxilia na montagem da AGM e procura o vértice de origem da rota escolhida
        //através do peso e seu destino.
        
        int origem = 0;

        for (int i = 0; i < listAdjacencia.size(); i++) {
            for (int j = 0; j < listAdjacencia.get(i).size(); j += 2) {
                if (listAdjacencia.get(i).get(j) == destino && listAdjacencia.get(i).get(j + 1) == peso) {
                    origem = i;
                    break;
                }

            }
        }
        return origem;
    }
}
