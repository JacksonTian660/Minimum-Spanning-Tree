#include "spanning_tree.h"

void spanning_tree(){
    number_of_vertex = 0, number_of_visited_vertex = 0, number_of_edge_sets =-1;

    printf("..................................Part 1: Graph scanning and Initializing....................................\n");

    char line[30];
    FILE *fp;
    
    fp = fopen("spanning_tree.txt", "r");
    while(fgets(line, 30, fp)!=NULL){
        number_of_edge_sets++;
    }
    printf("Number of edge sets %d\n", number_of_edge_sets);
    rewind(fp);

    // Scan the first line of the txt file to get number of vertices
    fscanf(fp,"%u",&number_of_vertex);

    // Check the number of Vertices
    printf("The number of vertices is %u\n", number_of_vertex);

    // dynamically allocate memory for unvisited nodes
    for(i=0;i<number_of_vertex;i++){
        unvisited[i] = 0;  
    }

    // edge set;
    edge_set_ptr = (edge_ptr)malloc((sizeof(edge)*number_of_edge_sets+1));

    int k = 0;
    while (!feof(fp)){
        fscanf(fp,"%u %u %u ",&edge_set_ptr[k].start, &edge_set_ptr[k].end, &edge_set_ptr[k].weight);
        
        // printf("Node number: %u\t Adjacent Node: %u\t Weight %u\n",edge_set_ptr[k].start, edge_set_ptr[k].end, edge_set_ptr[k].weight);
        k++;
    }

    printf("k: %d\n",k);
    // Check edge allocation
    printf("Node number: %u\t Adjacent Node: %u\t Weight %u\n",edge_set_ptr[0].start, edge_set_ptr[0].end, edge_set_ptr[0].weight);
    printf("Node number: %u\t Adjacent Node: %u\t Weight %u\n",edge_set_ptr[499999].start, edge_set_ptr[499999].end, edge_set_ptr[499999].weight);
    printf("Node number: %u\t Adjacent Node: %u\t Weight %u\n",edge_set_ptr[500000].start, edge_set_ptr[500000].end, edge_set_ptr[500000].weight);


    //A set pf vertex
    vertex_ptr linked_list_ptr = (vertex_ptr)malloc(sizeof(vertex)*number_of_vertex);
    for(i=0;i<number_of_vertex;i++){
        graph_vertex.data = i;
        graph_vertex.next = NULL;
        graph_vertex.distance = INF;
        linked_list_ptr[i] = graph_vertex;
    }


    // printf("Last line of Vertex: %d, %d, %p", linked_list_ptr[number_of_vertex-1].data, linked_list_ptr[number_of_vertex-1].distance, linked_list_ptr[number_of_vertex-1].next);  
    // printf("Last line of Vertex: %d, %d, %p", linked_list_ptr[number_of_vertex].data, linked_list_ptr[number_of_vertex].distance, linked_list_ptr[number_of_vertex].next);  

    fclose(fp);

    // printf("hello world\n");
    

    printf("\n...................................Part2 Processing...................................\n");


    int curr_vertex, number_of_vertex_in_path;
    number_of_visited = 0;
    int temp[20];

    vertex_ptr path;
    vertex newVertex;

    int vertex1, vertex2;

    int length_of_spanning_tree = 0;

    minimum_spanning_tree = malloc(sizeof(vertex)*(number_of_vertex-1));

    int starting_Vertex = 17345;
    unvisited[starting_Vertex] = 1;
    number_of_visited += 1;
    curr_vertex = starting_Vertex;


    printf("\n...................................Part2.1 Processing Startup...................................\n");

    while(number_of_visited!=number_of_vertex){
        unvisited[curr_vertex] = 1;
        number_of_visited ++;
        // printf("New Vertex: %d\n", curr_vertex);
        // printf("Number of visited: %d\n", number_of_visited);

        // if(number_of_visited == 10){
        //     break;
        // }
        
        int count = 0;
        for(i=0;i<number_of_edge_sets;i++){

            if(edge_set_ptr[i].start==curr_vertex && !unvisited[edge_set_ptr[curr_vertex].end]){
                temp[count] = edge_set_ptr[i].end;
                count++;
                
                // Update the vertice distance and prepare to select next vertex
                if(edge_set_ptr[i].weight < linked_list_ptr[edge_set_ptr[i].end].distance){
                    linked_list_ptr[edge_set_ptr[i].end].distance = edge_set_ptr[i].weight;

                    // Tracking update distace through which vertex and save them in the linkedlist;
                    path = &linked_list_ptr[edge_set_ptr[i].end];
                    if(path->next == NULL){
                        path->next = &linked_list_ptr[curr_vertex];
                    }
                    else{
                        newVertex.data = linked_list_ptr[curr_vertex].data;
                        newVertex.distance = linked_list_ptr[curr_vertex].distance;
                        newVertex.next = path->next;
                        path->next = &newVertex;
                    }

                }
            }

            //This is just for testing 
            // printf("%d\t%d\n", edge_set_ptr[i].end, edge_set_ptr[i].start);



            // This is used for if the end has the vertex value since this is not directed graph and update new distance
            if (edge_set_ptr[i].end==curr_vertex && !unvisited[edge_set_ptr[i].start]){
                count++;
                temp[count] = edge_set_ptr[i].start;

                int vertex_temp = edge_set_ptr[i].end;
                edge_set_ptr[i].end = edge_set_ptr[i].start;
                edge_set_ptr[i].start = vertex_temp;
                

                if(edge_set_ptr[i].weight < linked_list_ptr[edge_set_ptr[i].end].distance){
                    linked_list_ptr[edge_set_ptr[i].end].distance = edge_set_ptr[i].weight;

                    // Tracking update distace through which vertex and save them in the linkedlist;
                    path = &linked_list_ptr[edge_set_ptr[i].end];
                    if(path->next == NULL){
                        path->next = &linked_list_ptr[curr_vertex];
                    }
                    else{
                        newVertex.data = linked_list_ptr[curr_vertex].data;
                        newVertex.distance = linked_list_ptr[curr_vertex].distance;
                        newVertex.next = path->next;
                        path->next = &newVertex;
                    }

                }
                
            }
        }


        // printf("count: %d\n", count);
        for(i=0;i<count;i++){
        // printf("Connected Nodes %d\n and the update distance for this node is %d\n",temp[i],linked_list_ptr[temp[i]].distance);
        temp[i] = 0;
        }

        
        // Looking for the new vertex for the next iteration
        min_distance = INF;
        for(i=0;i<number_of_vertex;i++){
            if(!unvisited[i] && linked_list_ptr[i].distance < min_distance){
                min_distance = linked_list_ptr[i].distance;
                curr_vertex = i;
                // printf("Current Vertex %d\n", i);
                // printf("New Current Vertex %d\n", curr_vertex);
            }
        }

        

        
        // printf("%d %p\n\n",linked_list_ptr[19831].data, linked_list_ptr[19831].next);

        // printf("%d %p",linked_list_ptr[])
        if(linked_list_ptr[curr_vertex].next!=NULL){
            // This is the distance for new vertex
            vertex1 = linked_list_ptr[curr_vertex].data;
            // printf("vertex1: %d\n", vertex1);

            // This is the tracker for new vertex update distance throw which vertex;
            vertex2 = linked_list_ptr[curr_vertex].next->data;
            // printf("vertex2: %d\n", vertex2);

            // This is too copy information in the minimum spanning tree and then calculate length
            for(i=0;i<number_of_edge_sets;i++){
                if((edge_set_ptr[i].start==vertex1 && edge_set_ptr[i].end==vertex2)|| (edge_set_ptr[i].start==vertex2 && edge_set_ptr[i].end==vertex1)){
                    minimum_spanning_tree[number_of_visited-1].start = vertex1;
                    minimum_spanning_tree[number_of_visited-1].end = vertex2;
                    minimum_spanning_tree[number_of_visited-1].weight = edge_set_ptr[i].weight;
                    length_of_spanning_tree += minimum_spanning_tree[number_of_visited-1].weight;
                }
            }
        }

        
    }

    printf("The MST is below....................................\n");
    for(i=0;i<length_of_spanning_tree;i++){
        printf("(%d, %d  )",minimum_spanning_tree[i].start, minimum_spanning_tree[i].end);
    }

    printf("The length of the spanning tree is %d\n", length_of_spanning_tree);

    free(linked_list_ptr);
    free(minimum_spanning_tree);
    free(edge_set_ptr);
    

    
}    