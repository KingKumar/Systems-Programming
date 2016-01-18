// PipeRW.c

int i,y,a,b,c;
int x[2];
char alpha[26] = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";

void main(){
	y = pipe(x);
	a = fork();
	if (a == 0){
		close(x[0]);
		for(i = 0; i<500; i++){
			printf("\n%03d" + "aaa", i + 1);
		} 
		exit();
	}
	b = fork();
	if (b == 0){
		close(x[0]);
		for(i = 0; i<260; i++){
			if(i%10 == 0 && i != 0){
				b++;
			}
			printf("\n%s" + "x" + "%d", alpha[i%26], b);
		} 
		exit();
	}
	close(x[1]);
	//Read from pipe
	exit();
}

