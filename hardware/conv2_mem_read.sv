// counter/addresser for Convolution 2 layer output memory read (done)
module conv2_mem_read (input logic clk, reset, enable,
                        output logic [5:0] addr0, addr1, addr2, addr3,
                        output logic done);

    logic [1:0] count;
    always_ff @(posedge clk or posedge reset) begin
        if (reset == 1'b1) begin
            addr0 <= 6'b000000;
            addr1 <= 6'b000001;
            addr2 <= 6'b001000;
            addr3 <= 6'b001001;
            count <= 2'b00;
        end

        else if (enable == 1'b1 && done == 1'b0) begin
            if(count == 2'b11) begin
                count <= 2'b00;
                addr0 <= addr0 + 6'b001010;
                addr1 <= addr1 + 6'b001010;
                addr2 <= addr2 + 6'b001010;
                addr3 <= addr3 + 6'b001010;
            end
            else begin
                addr0 <= addr0 + 6'b000010;
                addr1 <= addr1 + 6'b000010;
                addr2 <= addr2 + 6'b000010;
                addr3 <= addr3 + 6'b000010;
                count <= count + 2'b01;
            end
        end
    end
    
    always_comb begin
        //stop when addr3 == 8^2 - 1, i.e. we have processed the entire image
        if(addr3 == 6'b111111) begin
            done = 1'b1;
        end
    end

endmodule