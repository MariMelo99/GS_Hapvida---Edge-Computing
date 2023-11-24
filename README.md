## Nome: Irana Pereira RM: 98593
## Nome: Mariana A Melo RM: 98121


### Este README fornece informações detalhadas sobre o projeto de Wowki e MQTT


Introdução:
Diante da preocupante estatística que revela uma taxa de mortalidade de 27% entre as pessoas com SEPSE em hospitais, e alarmantes 42% nas unidades de terapia intensiva, é crucial considerar a urgência de melhorias no processo de atendimento. Conforme a Organização Mundial da Saúde (OMS), a SEPSE representa uma proporção significativa, correspondendo a 27% das internações que resultam em óbito. Nesse contexto, é relevante notar que o atual protocolo de tratamento é manual, o que contribui para uma resposta mais lenta e menos eficaz.
O objetivo primordial deste projeto é digitalizar e armazenar esses dados de forma eletrônica, visando proporcionar maior celeridade no atendimento aos pacientes. A análise baseada nos sinais e sintomas da SEPSE e acidente vascular cerebral AVC,  é de extrema importância, considerando que tanto a SEPSE quanto o AVC podem resultar em sequelas se não forem identificados e tratados precocemente.
É comum observar que os protocolos de atendimento são frequentemente elaborados em papel e, posteriormente, inseridos nos sistemas, o que não apenas gera retrabalho, mas também consome tempo valioso. Assim, a proposta é modernizar e agilizar esse processo, garantindo uma abordagem mais eficiente na identificação e tratamento de condições críticas, minimizando o risco de sequelas e, em última instância, salvando vidas.


Protocolo SEPSE e AVC

SEPSE
A SEPSE é a disfunção de um ou mais órgãos decorrente da presença de uma infecção. Essa infecção pode ser grave, inicialmente, ou pode não ser tão grave, mas que não foi tratada ou não foi controlada adequadamente. É uma infecção que pode acarretar uma resposta inflamatória, inicialmente, no próprio órgão onde ela se originou e se estender e afetar outros órgãos também, causando uma inflamação em diferentes partes do corpo. A SEPSE acomete pessoas de qualquer idade, sendo mais comum em recém nascidos e pacientes idosos, mas afeta também aqueles que tenham algum grau de deficiência no sistema imune, que chamamos de imunossupressão.
Os principais sintomas são :
Febre ou hipotermia .
Confusão mental ou alteração do nível de consciência.
Diminuição do volume urinário.
Falta de ar .
Hipotensão.
Taquicardia, entre outros. 

AVC
Um acidente vascular cerebral é uma emergência médica.
Acontece quando vasos que levam sangue ao cérebro entopem ou se rompem, provocando a paralisia da área cerebral que ficou sem circulação sanguínea. É uma doença que acomete mais os homens e é uma das principais causas de morte, incapacitação e internações em todo o mundo.
Sinais e sintomas de AVC:
Os sintomas de acidente vascular cerebral incluem:
Dificuldade para andar,
Falar e compreender.
Paralisia ou dormência da face, do braço ou da perna.
Perda da força motora .

Saber identificar os sintomas de um acidente vascular cerebral (AVC), também conhecido como derrame, é crucial para obter bons resultados. O protocolo assistencial de AVC do Samaritano Higienópolis define os procedimentos adequados para o reconhecimento do problema, desde a entrada do paciente no hospital até a condução do devido encaminhamento, incluindo exames, tipo de tratamento para cada caso e prazos para que intervenções sejam realizadas. Ajuda a estabelecer, por exemplo, a necessidade de cirurgia ou medicamento e o tempo máximo em que ele deve ser administrado. O paciente que chega ao serviço de emergência tem seus sintomas neurológicos avaliados para a definição do tratamento trombolítico.




Funcionalidade proposta:
Desenvolver uma solução que facilite o diagnóstico e tratamento precoces da SEPSE e do AVC, visando melhorar a eficiência no atendimento, reduzir o tempo de resposta e, consequentemente, diminuir a taxa de mortalidade associada a essa condição.

Desenvolvimento:
Com a placa de ESP32 com apoio de LCD e buzzer e a comunicação da interface MQTT, pode ser enviado a mensagem do enfermeiro na triagem em atendimento ao paciete, assim que identifica o protocolo é direcionado ao médico via mensagem a informação se é SEPSE ou AVC e o médico decidir se a internação é imediata ou atendimento ambulatorial.
O LCD tem a função de uma tela de informação.
O intuito é prevenir o paciente de sequelas ou óbitos.

